#define N_RESOURCE_1 2
#define T_RESOURCE_1 1
#define N_RESOURCE_2 5
#define T_RESOURCE_2 10
#define N_RESOURCE_3 10
#define T_RESOURCE_3_LOW_LIMIT 5
#define T_RESOURCE_3_HIGH_LIMIT 15
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5

void utils_init(int seed);
void utils_term();
int rand_generator(int low_limit, int high_limit);
void sync_printf(const char *format, ...);
void wait_(int seconds);
unsigned int get_time_passed();

