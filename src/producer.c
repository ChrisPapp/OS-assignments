#include <stdio.h>
#include "producer.h"
#include "utils.h"
#include "theme.h"

void producer_init(struct producer *pd, struct theme *theme, int resource_1){
	pd->th = theme;
	resource_init(&pd->res_1, resource_1);
}

void producer_destroy(struct producer *pd) {
	resource_destroy(&pd->res_1);
}

void producer_place_request(struct producer *pd, int from_cust, int count) {
	int current_resource_id;
	pd->th->on_request_begin(from_cust, count);
	pthread_mutex_lock(&pd->res_1.lock);
	while (pd->res_1.available == 0) {
		pd->th->on_res_1_unavailable(from_cust);
		pthread_cond_wait(&pd->res_1.cond, &pd->res_1.lock);
	}
	current_resource_id = pd->res_1.available--;
	pthread_mutex_unlock(&pd->res_1.lock);
	int current_object = 0;
	while (current_object < count) {
		current_object++;
		pd->th->on_res_1_assign(from_cust, current_object);
		wait_(1); //kane kapoia douleia me ton paraskevasti
	}

	pthread_mutex_lock(&pd->res_1.lock);
	pd->th->on_request_complete(from_cust);
	pd->res_1.available++;
	pthread_cond_signal(&pd->res_1.cond);
	pthread_mutex_unlock(&pd->res_1.lock);
}


