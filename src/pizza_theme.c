#include <stdio.h>
#include "theme.h"
#include "utils.h"

static void pizza_begin_order(int client_id, int count) {
	printf("Hungry customer #%d ordered %d pizza(s)\n", client_id, count);
}

static void pizza_wait_cook(int client_id) {
	printf("No available cook found. Customer #%d will have to wait...\n", client_id);
}

static void pizza_prepare(int client_id, int obj_id) {
	printf("A cook is preparing pizza #%d for customer #%d\n", obj_id, client_id);
}

static void pizza_wait_oven(int client_id) {
	printf("No available oven found. Customer #%d will have to wait...\n", client_id);
}

static void pizza_in_oven(int client_id) {
	printf("Baking the pizza(s) of customer #%d! It smells nice! Almost done...\n", client_id);
}

static void pizza_order_complete(int client_id) {
	printf("Customer #%d got his pizza(s)\n", client_id);
}

void pizza_theme_init(struct theme *th) {
	th->on_request_begin = &pizza_begin_order;
	th->on_res_1_unavailable = &pizza_wait_cook;
	th->on_res_1_assign = &pizza_prepare;
	th->on_res_2_unavailable = &pizza_wait_oven;
	th->on_res_2_assign = &pizza_in_oven;
	th->on_request_complete = &pizza_order_complete;
}
