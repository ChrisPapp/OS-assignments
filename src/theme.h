#pragma once

struct theme {
	void(*on_request_begin)(int /*client_id */, int /*object count*/);
	void(*on_res_1_unavailable)(int /*client_id */);
	void(*on_res_1_assign)(int /*client_id */, int /* current_object */);
	void(*on_res_2_unavailable)(int /*client_id */);
	void(*on_res_2_assign)(int /*client_id */);
	void(*on_res_3_unavailable)(int /*client_id */);
	void(*on_res_3_assign)(int /*client_id */);
	void(*on_request_complete)(int /*client_id */, int /*work_time_resource_3*/, int /*clock*/);
	void(*terminate_producer)(float /*work_time_res_3_average_time*/, unsigned int /*work_time_res_3_max_time*/, float /*average_time*/, unsigned int /*max_time*/);
};

void pizza_theme_init(struct theme *th);
void corona_theme_init(struct theme *th);
