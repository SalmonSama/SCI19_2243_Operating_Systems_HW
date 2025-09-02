#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void INThandler(int sig);

int main(void) {
    signal(SIGINT, INThandler);  // Register Interrupt Handler
    while(1)
        pause();
    return 0;
}

void INThandler(int sig) {
    signal(SIGINT, SIG_IGN);    // Mask Signal
    printf("\nCtrl-C was hit !!!\nWant to quit? [y/n]\n");
    char input;
    input = getchar();
    if (input == 'y' || input == 'Y') {
        exit(0);
    } else {
        signal(SIGINT, INThandler); // Reregister Interrupt Handler
    }
}