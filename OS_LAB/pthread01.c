#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main(int argc, char *argv[]) {
	pthread_t tid; /* the thread identifier */	
	pthread_attr_t attr; /* set of attributes for the thread */
	
	if (argc != 2) {
		fprintf(stderr, "usage: pthread01 <integer value>\n");
		exit(1);
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "number must be >= 0\n");
		exit(2);
	}

	pthread_attr_init(&attr); /* get the default attributes */
	/* create the thread */
	pthread_create(&tid, &attr, runner, argv[1]);
	printf("I am mother therad, I will wait for my child thread\n");
	/* now wait for the thread to exit */
	//sleep(60);
	pthread_join(tid, NULL);
	printf("from my child sum = %d\n", sum);

	return 0;
}

void *runner(void *param) {
	int upper = atoi(param);
	int i;
	sum = 0;
	printf("I am child thread, I am calculating\n");
	if (upper > 0) {
		for (i = 1; i <= upper; i++)
			sum += i;
	}
	pthread_exit(NULL);
}