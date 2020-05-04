#pragma once
#include <pthread.h>

struct resource {
	pthread_mutex_t lock;
	pthread_cond_t  cond;
	int available;
};

void resource_init(struct resource *res, int available);
void resource_destroy(struct resource *res);

struct producer {
	struct theme *th;
	struct resource res_1;
	struct resource res_2;
	unsigned int sum_time;
	unsigned int max_time;
  static pthread_mutex_t max_time_mutex;
  static pthread_mutex_t sum_time_mutex;
};

void producer_init(struct producer *pd, struct theme *theme, int resource_1, int resource_2);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from, int count);
