#pragma once
#include <pthread.h>
#include "resource.h"

struct producer {
	struct theme *th;
	struct resource res_1;
	struct resource res_2;
	unsigned int average_time;
	unsigned int max_time;
};

void producer_init(struct producer *pd, struct theme *theme, int resource_1, int resource_2);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from, int count);
