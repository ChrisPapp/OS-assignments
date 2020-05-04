#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "producer.h"
#include "utils.h"
#include "theme.h"

struct theme *th;
struct producer *pd;

void *order(void *x) {
	int cust_id = *(int *)x;
  wait_(rand_generator(T_ORDER_LOW_LIMIT, T_ORDER_HIGH_LIMIT)); // customer's arrival
	producer_place_request(pd, cust_id, rand_generator(N_ORDER_LOW_LIMIT, N_ORDER_HIGH_LIMIT));
	pthread_exit(NULL);
}

void *order_instant(void *x) {
	int cust_id = *(int *)x;
	producer_place_request(pd, cust_id, rand_generator(N_ORDER_LOW_LIMIT, N_ORDER_HIGH_LIMIT));
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int *cust_id;
	int n_customers;
	unsigned int seed;
	pthread_t *ptr_threads;
	
	// checking arguments
	if (argc == 3) {
		n_customers = atoi(argv[1]);
		seed = atoi(argv[2]);
	} else {
		printf("Expected two integers as arguments ([number_of_customers] [rand_r_seed]). \n");
		exit(1);
	}

	// initialization step
	utils_init(seed);
	ptr_threads = (pthread_t *) malloc(sizeof(pthread_t) * n_customers);
	cust_id = (int *) malloc(sizeof(int) * n_customers);
	th = (struct theme *) malloc(sizeof(struct theme));
	pizza_theme_init(th);
	pd = (struct producer *) malloc(sizeof(struct producer));
	producer_init(pd, th, N_RESOURCE_1, N_RESOURCE_2);

	// execution step
	for (int i = 0; i < n_customers; i++) {
		cust_id[i] = i + 1;
		if (i == 0) {
			pthread_create(&ptr_threads[i], NULL, order_instant, &cust_id[i]);
		} else {
			pthread_create(&ptr_threads[i], NULL, order, &cust_id[i]);
		}
	}
	for (int i = 0; i < n_customers; i++) {
		pthread_join(ptr_threads[i], NULL);
	}

	// termination step
	pd->th->terminate_producer(pd->sum_time/n_customers, pd->max_time);
	producer_destroy(pd);
	utils_term();
	free(ptr_threads);
	free(pd);
	free(th);
	printf("\nPress Enter to continue");
	getchar();
	return 0;
}
