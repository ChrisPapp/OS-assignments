#pragma once
#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // _WIN32
#include <pthread.h>

struct producer {
	pthread_mutex_t lock;
	pthread_cond_t  cond;
	int resource_1;
};

void producer_init(struct producer *pd, int resource_1);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from);