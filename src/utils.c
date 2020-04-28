#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include "utils.h"

static pthread_mutex_t printf_mutex;
static unsigned int rand_r_seed;
static unsigned int current_time_in_seconds();
static unsigned int clock_start;

void utils_init(int seed) {
	rand_r_seed = seed;
	if (pthread_mutex_init(&printf_mutex, NULL) != 0) {
		printf("Error in printf_mutex initialization.");
		exit(1);
	}
	clock_start = current_time_in_seconds();
}
 
void utils_term() {
  pthread_mutex_destroy(&printf_mutex);
}

void sync_printf(const char *format, ...) {
	// https://stackoverflow.com/questions/23586682/how-to-use-printf-in-multiple-threads
	va_list args;
    va_start(args, format);
    pthread_mutex_lock(&printf_mutex);
    vprintf(format, args);
    pthread_mutex_unlock(&printf_mutex);
    va_end(args);
}

int rand_r_generator() {
	return T_ORDER_LOW_LIMIT + (rand_r_(&rand_r_seed) % T_ORDER_HIGH_LIMIT);
}

int rand_r_(unsigned int *seed) {
#ifdef _WIN32
	// https://code.woboq.org/userspace/glibc/stdlib/rand_r.c.html
	unsigned int next = *seed;
	int result;
	next *= 1103515245;
	next += 12345;
	result = (unsigned int)(next / 65536) % 2048;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;
	*seed = next;
	return result;
#else
	return rand_r(seed);
#endif
}

void wait_(int seconds) {
#ifdef _WIN32
	Sleep(1000 * seconds);
#else
	sleep(seconds);
#endif
}

static unsigned int current_time_in_seconds() {
#ifdef _WIN32
	return 0;
#else
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return time.tv_sec;
#endif // _WIN32
}

unsigned int get_time_passed() {
	return current_time_in_seconds() - clock_start;
}
