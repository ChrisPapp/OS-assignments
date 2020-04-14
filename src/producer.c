#include <stdio.h>
#include "producer.h"

void producer_init(struct producer *pd, int resource_1)
{
	pthread_mutex_init(&pd->lock, NULL);
	pthread_cond_init(&pd->cond, NULL);
	pd->resource_1 = resource_1;
}

void producer_destroy(struct producer *pd)
{
	pthread_mutex_destroy(&pd->lock);
	pthread_cond_destroy(&pd->cond);
}

void producer_place_request(struct producer *pd, int from)
{
	printf("Client #%d made a request\n", from);
	pthread_mutex_lock(&pd->lock);
	while (pd->resource_1 == 0) {
		printf("Waiting for resource 1...\n", from);
		pthread_cond_wait(&pd->cond, &pd->lock);
	}
	printf("Resource 1 working on client #%d's request.\n", from);
	pd->resource_1--;
	pthread_mutex_unlock(&pd->lock);

	wait_(0); //kane kapoia douleia me ton paraskevasti

	pthread_mutex_lock(&pd->lock);
	printf("Client #1's request complete! \n", from);
	pd->resource_1++;
	pthread_cond_signal(&pd->cond);
	pthread_mutex_unlock(&pd->lock);
}