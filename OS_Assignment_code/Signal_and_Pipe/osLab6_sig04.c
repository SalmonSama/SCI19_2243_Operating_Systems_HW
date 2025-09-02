#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

signed long prev, i; // Global Variables

void USRhandler(int sig);

int main(void) {
    signed long curr;
    signal(SIGUSR1, USRhandler); // Register SIGUSR1 Handler
    for (prev = i = 1; ; i++, prev = curr) {
        curr = prev * i;
        if (curr < prev) {
            raise(SIGUSR1); // Raise SIGUSR1 to Handler
        } else {
            printf(" %ld! = %ld (%ld)\n", i, curr, prev);
        }
    }
    return 0;
}

void USRhandler(int sig) {
    printf("Received SIGUSR1. The max is %ld! = %ld\n", i - 1, prev);
    exit(0);
}
