#include <stdio.h>
#include "theme.h"

static void pizza_begin_order(int client_id) {
	printf("Preparing pizzas for customer #%d\n", client_id);
}

void pizza_theme_init(struct theme *th) {
	th->on_request_begin = &pizza_begin_order;
}