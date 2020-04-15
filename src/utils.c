#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#endif
#include "utils.h"

void initialize_mutex() {
  if (pthread_mutex_init(&printf_lock, NULL) != 0) {
    printf("error in mutex initialization");
    exit(1);
  }
}
 
void terminate_mutex() {
  pthread_mutex_destroy(&printf_lock);
}

void print(char message[128]) {
	pthread_mutex_lock(&printf_lock);
	printf("%s", message);
	pthread_mutex_unlock(&printf_lock);
}

int rand_r_generator(unsigned int *seed) {
	return T_ORDER_LOW_LIMIT + (rand_r_(seed) % T_ORDER_HIGH_LIMIT);
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

