#include <stdlib.h>
#include <stdio.h>
#include "producer.h"
#include "utils.h"
#include "theme.h"

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // _WIN32
#include <pthread.h>

#define N_COOK 6
#define N_OVEN 5
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5
#define T_PREPARE 1
#define T_BAKE 5

#define N 10 // gia na trexei to paradeigma
int cooks = 2; //diathesimoi paraskevastes
int id[N];
struct theme *th;
struct producer *pd;

int rand_r_generator(unsigned int *seed) {
	return T_ORDER_LOW_LIMIT + (rand_r_(seed) % T_ORDER_HIGH_LIMIT);
}

void *order(void *x) {
	int id = *(int *)x;

	producer_place_request(pd, id);
	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {
	unsigned int seed;
	int rc;
	int n_customer;
	pthread_t threads[N];
		
	if (argc == 3) {
		n_customer = atoi(argv[1]);
		seed = atoi(argv[2]);
	} else {
		printf("Expected two Integers \n");
		exit(1);
	}

	th = (struct theme *) malloc(sizeof(struct theme));
	pizza_theme_init(th);
	pd = (struct producer *) malloc(sizeof(struct producer));
	producer_init(pd, th, cooks);

	for (int i = 0; i < N; i++) {
		id[i] = i + 1;
		printf("Main: creating thread %d\n", i + 1);
		rc = pthread_create(&threads[i], NULL, order, &id[i]);
	}

	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	producer_destroy(pd);
	free(pd);
	free(th);
	printf("Press Enter to continue");
	getchar();
	return 0;
}


