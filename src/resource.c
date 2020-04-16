#include "resource.h"

void resource_init(struct resource *res, int available) {
	pthread_mutex_init(&res->lock, NULL);
	pthread_cond_init(&res->cond, NULL);
	res->available = available;
}

void resource_destroy(struct resource *res) {
	pthread_mutex_destroy(&res->lock);
	pthread_cond_destroy(&res->cond);
}
