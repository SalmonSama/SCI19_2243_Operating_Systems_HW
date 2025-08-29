#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define clear_buffer() while(getchar() != '\n')

void int_handler(int);

void main(void) {
	signal(SIGINT, int_handler);
	while (1) {
		printf("Running ... \n");
		sleep(1);
	}
}

void int_handler(int sig) {
	char c;

	signal(sig, SIG_IGN); 		/* disable Ctrl-C */
	printf("OUCH, did you hit Ctrl-C?\n Do you really want to quit? [y/n]");

	c = getchar();			/* read an input character */
	clear_buffer();

	if (c == 'y' || c == 'Y') { 	/* if it is y or Y, then exit. */
		exit(0);
	} else {			/* reinstall the handler */
		signal(SIGINT, int_handler);
	}
}