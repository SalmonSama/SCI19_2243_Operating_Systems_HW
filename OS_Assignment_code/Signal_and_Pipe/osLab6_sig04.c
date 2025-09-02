#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

signed long prev, i;    // Global Variables

void USR1handler(int sig);

void USR1handler(int sig) {
    printf("Received SIGUSR1. The max is %ld! = %ld\n", i - 1, prev);
    exit(0);
}

int main(void) {
    signed long curr;

    signal(SIGUSR1, USR1handler);   // Register SIGUSR1 Handler

    for (prev = i = 1; ; i++, prev = curr) {
        curr = prev * i;
        if (curr < prev) {
            raise(SIGUSR1); // Raise SIGUSR1 to Handler
        } else {
            printf(" %ld! = %ld\n", i, curr);    
        }
    }

    return 0;
}