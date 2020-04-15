#pragma once
#include <pthread.h>
#include "resource.h"

struct producer {
	struct theme *th;
	struct resource res_1;
};

void producer_init(struct producer *pd, struct theme *theme, int resource_1);
void producer_destroy(struct producer *pd);
void producer_place_request(struct producer *pd, int from, int count);
