#include <stdio.h>
#include <stdlib.h>

#ifdef WINDOWS_VS
#define HAVE_STRUCT_TIMESPEC // https://stackoverflow.com/questions/33557506/timespec-redefinition-error
#endif // WINDOWS_VS
#include <pthread.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define N_COOK 6
#define N_OVEN 5
#define T_ORDER_LOW_LIMIT 1
#define T_ORDER_HIGH_LIMIT 5
#define N_ORDER_LOW_LIMIT 1
#define N_ORDER_HIGH_LIMIT 5
#define T_PREPARE 1
#define T_BAKE 5

#define N 10 // gia na trexei to paradeigma

pthread_mutex_t lock;
pthread_cond_t  cond;
int cooks = 2; //diathesimoi paraskevastes
int id[N];

void srand_seed_initializer(int srand_seed) {
	srand(srand_seed);	
}

int rand_generator() {
	return T_ORDER_LOW_LIMIT + (rand() % T_ORDER_HIGH_LIMIT);
}

void wait_(int seconds)
{
#ifdef _WIN32
	Sleep(1000 * seconds);
#else
	sleep(seconds);
#endif
}

void *order(void *x) {

	int id = *(int *)x;
	int rc;
	printf("Hello from order: %d\n", id);

	rc = pthread_mutex_lock(&lock);
	while (cooks == 0) {
		printf("H paraggelia %d, den brike diathesimo paraskevasti. Blocked...\n", id);
		rc = pthread_cond_wait(&cond, &lock);
	}
	printf("H paraggelia %d eksipiretitai.\n", id);
	cooks--;
	rc = pthread_mutex_unlock(&lock);

	wait_(2); //kane kapoia douleia me ton paraskevasti

	rc = pthread_mutex_lock(&lock);
	printf("H paraggelia %d eksipiretithike epitixos! \n", id);
	cooks++;
	rc = pthread_cond_signal(&cond);
	rc = pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
	int rc;
	int srand_seed;
	int n_customer;
	pthread_t threads[N];
		
	if (argc == 3) {
		n_customer = atoi(argv[1]);
		srand_seed = atoi(argv[2]);
	} else {
		printf("Expected two Integers \n");
		exit(1);
	}
	srand_seed_initializer(srand_seed);

	/*
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);

	for (int i = 0; i < N; i++) {
		id[i] = i + 1;
		printf("Main: creating thread %d\n", i + 1);
		rc = pthread_create(&threads[i], NULL, order, &id[i]);
	}

	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);

	return 0;
	*/
}


