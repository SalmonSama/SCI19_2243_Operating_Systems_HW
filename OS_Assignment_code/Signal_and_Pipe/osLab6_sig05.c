#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define SLEEP 3

int flag = 1;
int count = 0; // Global Variables

void mySIGhandler(int sig);

void main() {
    clock_t start;
    pid_t pid;
    signal(SIGUSR2, mySIGhandler); // Register Signal Handler
    if ((pid = fork()) < 0) { // Fork process
        printf("fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        sleep(SLEEP);
        printf("Child sending signal ...\n");
        kill(getppid(), SIGUSR2); // Send signal to parent process
        exit(0);
    } else { // Parent process
        printf("Parent waiting signal ...\n");
        start = clock();
        while (flag) count += 1;
        printf("It takes %d loops\n", count);
        printf("It takes %.2f sec.\n", (double)((clock() - start) / CLOCKS_PER_SEC));
    }
}

void mySIGhandler(int sig) {
    signal(SIGUSR2, SIG_IGN); // Mask Signal
    flag = 0;
}