#include <stdio.h>
#include <stdlib.h>
#ifdef WINDOWS_VS
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // WINDOWS_VS

#include <pthread.h>

#define NUM_THREADS	5

void *say_hello(void *tid)
{
	int id = *(int *)tid;
	printf("Hello from thread %d\n", id);
	free(tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	for (int t = 0; t < NUM_THREADS; t++) {
		int *id = malloc(sizeof(int));
		*id = t + 1;
		if (pthread_create(&threads[t], NULL, &say_hello, id)) {
			printf("Thread creation failed");
			exit(-1);
		}
	}
	for (int t = 0; t < NUM_THREADS; t++) {
		pthread_join(threads[t], NULL);
	}
	pthread_exit(NULL);
}