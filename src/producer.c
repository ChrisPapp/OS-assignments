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
  int time_working_res_3;
	int clock_start, clock_stop, time_passed;

  /* before */
	clock_start = get_time_passed(); // clock starts ticking

	/* main process */
	pd->th->on_request_begin(from_cust, count);
	// starting journey through resource_1
	resource_commit(&pd->res_1);
	int current_object = 0;
	while (current_object < count) {
		current_object++;
		pd->th->on_res_1_assign(from_cust, current_object);
		wait_(T_RESOURCE_1); // working resource_1
	}
	// starting journey through resource_2
	resource_commit(&pd->res_2);
	pd->th->on_res_2_assign(from_cust);
	// releasing resource_1
	resource_release(&pd->res_1);
  // continue journey through resource_2
	wait_(T_RESOURCE_2); // working resource_2
	// starting journey through resource_3
	resource_commit(&pd->res_3);
	pd->th->on_res_3_assign(from_cust);
	// releasing resource_2
  resource_release(&pd->res_2);
  // continue journey through resource_3
	time_working_res_3 = rand_generator(T_RESOURCE_3_LOW_LIMIT, T_RESOURCE_3_HIGH_LIMIT);
	wait_(time_working_res_3); // working resource_3 part 1
	pd->th->on_request_complete(from_cust, time_passed);
	wait_(time_working_res_3); // working resource_3 part 2
  // releasing resource_3
  resource_release(&pd->res_3);
  
  /* after */
	// request completed
	clock_stop = get_time_passed();
	time_passed = clock_stop - clock_start;
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

