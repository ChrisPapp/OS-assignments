#include <stdio.h>
#include "theme.h"
#include "utils.h"

static void corona_requests_sanitizer(int client_id, int count) {
	sync_printf("Masked grandpa #%d came at the pharmacy after %u minutes looking for %d hand sanitizer(s)\n", client_id, get_time_passed(), count);
}

static void corona_wait_pharmacy(int client_id) {
	sync_printf("No avaiable pharmacist found. Masked grandpa #%d will have to wait...\n", client_id);
}

static void sanitizer_prepare(int client_id, int obj_id) {
	sync_printf("A pharmacist is preparing hand sanitizer #%d for masked grandpa #%d\n", obj_id, client_id);
}

static void sanitizer_no_alcohol(int client_id) {
	sync_printf("No more ethyl alcohol on planet earth. Crazy grandpa #%d will have to wait...\n", client_id);
}

static void sanitizer_mixing(int client_id) {
	sync_printf("Mixing sanitizers of crazy grandpa #%d with fake ethyl alcohol aka gasoline! It smells nice! Almost done...\n", client_id);
}

static void sanitizers_complete(int client_id, int clock) {
	sync_printf("Crazy grandpa #%d got his hand sanitizers in about %d months\n", client_id, clock);
}

static void closing_pharmacy(unsigned int average_time, unsigned int max_time) {
  sync_printf("Average time: %d (rounded), Maximum time: %d ", average_time, max_time);
}

void corona_theme_init(struct theme *th) {
	th->on_request_begin = &corona_requests_sanitizer;
	th->on_res_1_unavailable = &corona_wait_pharmacy;
	th->on_res_1_assign = &sanitizer_prepare;
	th->on_res_2_unavailable = &sanitizer_no_alcohol;
	th->on_res_2_assign = &sanitizer_mixing;
	th->on_request_complete = &sanitizers_complete;
	th->terminate_producer = &closing_pharmacy;
}
