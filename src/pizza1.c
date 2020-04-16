#include <stdlib.h>
#include <stdio.h>
#include "producer.h"
#include "utils.h"
#include "theme.h"

#include <pthread.h>

unsigned int seed;
struct theme *th;
struct producer *pd;

void *order(void *x) {
	int cust_id = *(int *)x;
	producer_place_request(pd, cust_id, rand_r_generator(&seed));
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int rc;
	int cust_id;
	int n_customers;
	pthread_t *ptr_threads;
		
	if (argc == 3) {
		n_customers = atoi(argv[1]);
		seed = atoi(argv[2]);
	} else {
		printf("Expected two Integers \n");
		exit(1);
	}

	ptr_threads = (pthread_t *) malloc(sizeof(pthread_t) * n_customers);
	
	th = (struct theme *) malloc(sizeof(struct theme));
	pizza_theme_init(th);
	pd = (struct producer *) malloc(sizeof(struct producer));
	producer_init(pd, th, N_RESOURCE_1, N_RESOURCE_2);

	for (int i = 0; i < n_customers; i++) {
		cust_id = i + 1;
		printf("Main: creating thread %d\n", cust_id);
		rc = pthread_create(&ptr_threads[i], NULL, order, &cust_id);
	}

	for (int i = 0; i < n_customers; i++) {
		pthread_join(ptr_threads[i], NULL);
	}

	producer_destroy(pd);
	free(ptr_threads);
	free(pd);
	free(th);
	printf("\nPress Enter to continue");
	getchar();
	return 0;
}
