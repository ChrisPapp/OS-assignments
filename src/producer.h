#pragma once
#ifdef WINDOWS_VS
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // WINDOWS_VS
#include <pthread.h>

struct producer {
	pthread_mutex_t lock;
	pthread_cond_t  cond;
	int resource_1;
};
void producer_init(struct producer *pd, int resource_1);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from);