#pragma once
#include <pthread.h>
#include "resource.h"

struct producer {
  struct theme *th;
  struct resource res_1;
  struct resource res_2;
  unsigned int sum_time;
  unsigned int max_time;
  pthread_mutex_t max_time_mutex;
  pthread_mutex_t sum_time_mutex;
};

void producer_init(struct producer *pd, struct theme *theme, int resource_1, int resource_2);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from, int count);
void producer_check_if_time_max(struct producer *pd, int time);
void producer_increment_time(struct producer *pd, int time);
