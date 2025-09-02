#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void SIGhandler(int sig);

void main() {
    signal(SIGINT, SIGhandler);
    // Register Ctrl-C handler
    while (1) {
        printf("Going to sleep for a second ...\n");
        sleep(1);
    }
}

void SIGhandler(int sig) {
    printf("Caught signal %d, coming out ...\n", sig);
    exit(0);
}
