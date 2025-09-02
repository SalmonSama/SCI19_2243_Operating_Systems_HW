#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
    pid_t pid;
    if ((pid = fork()) < 0) { // Fork process
        printf("fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        printf("Child created\n");
        while (1);
        printf("Hello from child :)\n");
    } else { // Parent process
        printf("Parent created\n");
        sleep(3);
        printf("Hello from parent :)\n");
        kill(pid, SIGKILL); // Send kill signal to child process
    }
}