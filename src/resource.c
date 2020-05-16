#include <pthread.h>
#include "resource.h"
#include "theme.h"

void resource_init(struct resource *res, int available) {
	pthread_mutex_init(&res->lock, NULL);
	pthread_cond_init(&res->cond, NULL);
	res->available = available;
}

void resource_destroy(struct resource *res) {
	pthread_mutex_destroy(&res->lock);
	pthread_cond_destroy(&res->cond);
}

void resource_commit(struct resource *res) {
  pthread_mutex_lock(&res->lock);
	while (res->available == 0) {
		pthread_cond_wait(&res->cond, &res->lock);
	}
	res->available--;
	pthread_mutex_unlock(&res->lock);
}

void resource_release(struct resource *res) {
  pthread_mutex_lock(&res->lock);
	res->available++;
	pthread_cond_signal(&res->cond);
	pthread_mutex_unlock(&res->lock);
}
