#include <stdlib.h>
#include <stdio.h>
#include "producer.h"
#include "utils.h"
#include "theme.h"

#include <pthread.h>

#define N 4 // gia na trexei to paradeigma
int cooks = 2; //diathesimoi paraskevastes
int id[N];
struct theme *th;
struct producer *pd;

void *order(void *x) {
	int cust_id = *(int *)x;

	producer_place_request(pd, cust_id, 10);
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
	producer_init(pd, th, N_COOK);

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
