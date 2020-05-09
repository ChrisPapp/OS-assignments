#pragma once
#include <pthread.h>

struct resource {
  pthread_mutex_t lock;
  pthread_cond_t cond;
  int available;
};

void resource_init(struct resource *res, int available);
void resource_destroy(struct resource *res);
void resource_commit(struct resource *res);
void resource_release(struct resource *res);
