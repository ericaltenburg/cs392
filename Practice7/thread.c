/* Eric Altenburg
 * I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <pthread.h>

// Global var
int counter = 0;
//pthread_mutex_t lock;

void* run_thread (void* noarg) {
//	pthread_mutex_lock(&lock);
	
	int i = 0;
	for( i = 0; i < 100000; i++) {
		counter ++;
	}
	pthread_exit(NULL);
//	pthread_mutex_unlock(&lock);
	return NULL;
}

int main() {
//	if (pthread_mutex_init(&lock, NULL) != 0) {
//		printf("\nmutex init has failed\n");
//		return 1;
	// }	

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, run_thread, NULL);
	pthread_create(&thread2, NULL, run_thread, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("The final counter is %d\n", counter);
//	pthread_mutex_destroy(&lock);
	return 0;
}
