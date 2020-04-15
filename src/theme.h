
#pragma once
struct theme {
	void(*on_request_begin)(int /*client_id */);
};

void pizza_theme_init(struct theme *th);
