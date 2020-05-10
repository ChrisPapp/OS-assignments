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
static pthread_mutex_t rand_n_mutex;
static unsigned int current_time_in_seconds();
static unsigned int clock_start;

void utils_init(int seed) {
	srand(seed);
  if (pthread_mutex_init(&rand_n_mutex, NULL) != 0) {
		printf("Error in rand_n_mutex initialization.");
		exit(1);
	}
	if (pthread_mutex_init(&printf_mutex, NULL) != 0) {
		printf("Error in printf_mutex initialization.");
		exit(1);
	}
	clock_start = current_time_in_seconds();
}
 
void utils_term() {
  pthread_mutex_destroy(&printf_mutex);
  pthread_mutex_destroy(&rand_n_mutex);
}

int rand_generator(int low_limit, int high_limit) {
  int rand_n;
  int diff;
  pthread_mutex_lock(&rand_n_mutex);
  diff = high_limit - low_limit;
  rand_n = low_limit + (rand() % (diff + 1));
  pthread_mutex_unlock(&rand_n_mutex);
	return rand_n;
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
