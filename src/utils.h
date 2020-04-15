#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // _WIN32
#include <pthread.h>

#define N_COOK 6
#define N_OVEN 5
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5
#define T_PREPARE 1
#define T_BAKE 5

pthread_mutex_t printf_lock;

void initialize_mutex();
void terminate_mutex();
void print(char message[128]);
int rand_r_generator(unsigned int *seed);
int rand_r_(unsigned int *seed);
void wait_(int seconds);

