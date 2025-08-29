#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

signed long prev_fact, i;

void sig_handler(int);

void sig_handler(int sig) {
	printf("\nReceived a SIGUSR1. The answer is %ld! = %ld\n", i-1, prev_fact);
	exit(0);
}

int main(void) {
	signed long fact;
	
	printf("Factorial Computation\n\n");
	signal(SIGUSR1, sig_handler);
	for (prev_fact = i = 1; ; i++, prev_fact = fact) {
		fact = prev_fact * i;
		if (fact < prev_fact) {
			raise(SIGUSR1);
		} else {
			printf("%ld! = %ld (%ld)\n", i, fact, prev_fact);
		}
	}

	return 0;
}