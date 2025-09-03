#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int c_pid; // Global Variable

void main() {
    pid_t pid;
    if ((pid = fork()) < 0) { // Fork process
        printf("fork failed");
        exit(1);
    } else if (pid == 0) { // Child process
        c_pid = getpid(); 
        printf("Child created\n");
        while (1); 
        printf("Hello from child :)\n");
    } else { // Parent process
        printf("Parent created\n");
        sleep(3);
        printf("Hello from parent :)\n");
        kill(c_pid, SIGKILL); // Send kill signal to child process
    }
}