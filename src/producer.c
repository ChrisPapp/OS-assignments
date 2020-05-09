#include <stdio.h>
#include "producer.h"
#include "resource.h"
#include "utils.h"
#include "theme.h"


void producer_init(struct producer *pd, struct theme *theme, int resource_1, int resource_2, int resource_3){
	pd->th = theme;
	pd->sum_time = 0;
	pd->max_time = 0;
	resource_init(&pd->res_1, resource_1);
	resource_init(&pd->res_2, resource_2);
	resource_init(&pd->res_3, resource_3);
  if (pthread_mutex_init(&pd->max_time_mutex, NULL) != 0) {
		printf("Error in max_time_mutex initialization.");
	}
  if (pthread_mutex_init(&pd->sum_time_mutex, NULL) != 0) {
		printf("Error in sum_time_mutex initialization.");
	}
}

void producer_destroy(struct producer *pd) {
	resource_destroy(&pd->res_1);
	resource_destroy(&pd->res_2);
	resource_destroy(&pd->res_3);
  pthread_mutex_destroy(&pd->max_time_mutex);
  pthread_mutex_destroy(&pd->sum_time_mutex);
}

void producer_place_request(struct producer *pd, int from_cust, int count) {
	int current_resource_1_id;
	int current_resource_2_id;
	int current_resource_3_id;
	int time_working_res_3;
	int clock_start, clock_stop, time_passed;

	clock_start = get_time_passed(); // clock starts ticking
	pd->th->on_request_begin(from_cust, count);

	// journey through resource_1
	pthread_mutex_lock(&pd->res_1.lock);
	while (pd->res_1.available == 0) {
		pd->th->on_res_1_unavailable(from_cust);
		pthread_cond_wait(&pd->res_1.cond, &pd->res_1.lock);
	}
	current_resource_1_id = pd->res_1.available--;
	pthread_mutex_unlock(&pd->res_1.lock);
	int current_object = 0;
	while (current_object < count) {
		current_object++;
		pd->th->on_res_1_assign(from_cust, current_object);
		wait_(T_RESOURCE_1); // working
	}

	// journey through resource_2
	pthread_mutex_lock(&pd->res_2.lock);
	while (pd->res_2.available == 0) {
		pd->th->on_res_2_unavailable(from_cust);
		pthread_cond_wait(&pd->res_2.cond, &pd->res_2.lock);
	}
	current_resource_2_id = pd->res_2.available--;
	pthread_mutex_unlock(&pd->res_2.lock);
	pd->th->on_res_2_assign(from_cust);
	wait_(T_RESOURCE_2); // working

	// releasing resource_1
	pthread_mutex_lock(&pd->res_1.lock);
	pd->res_1.available++;
	pthread_cond_signal(&pd->res_1.cond);
	pthread_mutex_unlock(&pd->res_1.lock);

	// starting journey through resource_3
  pthread_mutex_lock(&pd->res_3.lock);
	while (pd->res_3.available == 0) {
		pd->th->on_res_3_unavailable(from_cust);
		pthread_cond_wait(&pd->res_3.cond, &pd->res_3.lock);
	}
	current_resource_3_id = pd->res_3.available--;
	pthread_mutex_unlock(&pd->res_3.lock);

	// releasing resource_2
	pthread_mutex_lock(&pd->res_2.lock);
	pd->res_2.available++;
	pthread_cond_signal(&pd->res_2.cond);
	pthread_mutex_unlock(&pd->res_2.lock);
  
  // continue journey through resource_3
	time_working_res_3 = rand_generator(T_RESOURCE_3_LOW_LIMIT, T_RESOURCE_3_HIGH_LIMIT);
	wait_(time_working_res_3); // working part 1
	pd->th->on_res_3_assign(from_cust);
	wait_(time_working_res_3); // working part 2

  // releasing resource_3
	pthread_mutex_lock(&pd->res_3.lock);
	pd->res_3.available++;
	pthread_cond_signal(&pd->res_3.cond);
	pthread_mutex_unlock(&pd->res_3.lock);
	
	// request completed
	clock_stop = get_time_passed();
	time_passed = clock_stop - clock_start;
	pd->th->on_request_complete(from_cust, time_passed);
	// update time counters
	producer_check_if_time_max(pd, time_passed);
	producer_increment_time(pd, time_passed);
}

void producer_increment_time(struct producer *pd, int time) {
  pthread_mutex_lock(&pd->sum_time_mutex);
  pd->sum_time += time; // summarizing time
  pthread_mutex_unlock(&pd->sum_time_mutex);
}

void producer_check_if_time_max(struct producer *pd, int time) {
  pthread_mutex_lock(&pd->max_time_mutex);
	if (pd->max_time < time) {
		pd->max_time = time;
	}
	pthread_mutex_unlock(&pd->max_time_mutex);
}

