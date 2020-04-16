#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#define N_RESOURCE_1 6
#define N_RESOURCE_2 5
#define T_RESOURCE_1 1
#define T_RESOURCE_2 5
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5

static pthread_mutex_t printf_mutex;
static unsigned int rand_r_seed;

void utils_init();
void utils_term();
void sync_printf(const char *format, ...);
int rand_r_generator();
int rand_r_(unsigned int *seed);
void wait_(int seconds);
