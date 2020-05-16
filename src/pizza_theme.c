#include <stdio.h>
#include "theme.h"
#include "utils.h"

static void pizza_begin_order(int client_id, int count) {
	sync_printf("Hungry customer #%d appeared after %u minutes and ordered %d pizza(s)\n", client_id, get_time_passed(), count);
}

static void pizza_wait_cook(int client_id) {
	sync_printf("No available cook found. Order of customer #%d is pending... \n", client_id);
}

static void pizza_prepare(int client_id, int obj_id) {
	sync_printf("A cook is preparing pizza #%d for customer #%d\n", obj_id, client_id);
}

static void pizza_wait_oven(int client_id) {
	sync_printf("No available oven found. Order of customer #%d is pending...\n", client_id);
}

static void pizza_in_oven(int client_id) {
	sync_printf("Baking the pizza(s) of customer #%d! Mmmmmmmmmmmmm! It smells nice!\n", client_id);
}

static void pizza_wait_delivery_person(int client_id) {
  sync_printf("No available delivery person found. Order of customer #%d is pending....\n", client_id);
}

static void pizza_on_the_road(int client_id) {
  sync_printf("Pizzas of customer #%d were taken off the oven and are on the way.\n", client_id);
}

static void pizza_order_complete(int client_id, int time_cooling, int clock) {
	sync_printf("Order of customer #%d is delivered after %d minutes and was getting cold for %d minutes.\n", client_id, clock, time_cooling);
}

static void closing_pizzeria(unsigned int cooling_average_time, unsigned int cooling_max_time, unsigned int average_time, unsigned int max_time) {
  sync_printf("\n");
  sync_printf("Average cooling time: %d (rounded), Maximum cooling time: %d", cooling_average_time, cooling_max_time);
  sync_printf("\n");
  sync_printf("Average time: %d (rounded), Maximum time: %d", average_time, max_time);
  sync_printf("\n");
}

void pizza_theme_init(struct theme *th) {
	th->on_request_begin = &pizza_begin_order;
	th->on_res_1_unavailable = &pizza_wait_cook;
	th->on_res_1_assign = &pizza_prepare;
	th->on_res_2_unavailable = &pizza_wait_oven;
	th->on_res_2_assign = &pizza_in_oven;
	th->on_res_3_unavailable = &pizza_wait_delivery_person;
	th->on_res_3_assign = &pizza_on_the_road;
	th->on_request_complete = &pizza_order_complete;
	th->terminate_producer = &closing_pizzeria;
}
