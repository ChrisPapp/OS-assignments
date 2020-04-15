#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif



void wait_(int seconds)
{
#ifdef _WIN32
	Sleep(1000 * seconds);
#else
	sleep(seconds);
#endif
}


int
rand_r_(unsigned int *seed)
{
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