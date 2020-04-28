#define N_RESOURCE_1 6
#define N_RESOURCE_2 5
#define T_RESOURCE_1 1
#define T_RESOURCE_2 5
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5

void utils_init(int seed);
void utils_term();
void sync_printf(const char *format, ...);
int rand_r_generator();
int rand_r_(unsigned int *seed);
void wait_(int seconds);
unsigned int get_time_passed();
