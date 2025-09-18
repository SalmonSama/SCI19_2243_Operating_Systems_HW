#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "osLab08_peterson.h" // Assuming this is the correct header name

void parentProcess(int *);
void childProcess(int *);

int main(int argc, char *argv[]) {
    int shmID, status, *count;
    int round = 10;
    pid_t pid; // Variable to hold the process ID

    // Create and attach shared memory for the counter
    shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    count = (int *) shmat(shmID, NULL, 0);
    *count = 99;

    initializePeterson(); // Initialize Peterson's algorithm

    pid = fork(); // Create a new process

    if (pid == 0) { //  <--- 1.1: fork() returns 0 in the child process
        // Child's code block
        for (int i = 0; i < round; i++) {
            childProcess(count);
        }
        exit(0);
    }

    // Parent's code block
    for (int i = 0; i < round; i++) {
        parentProcess(count); // <--- 1.2: Parent calls its function in a loop
    }

    wait(&status); // Wait for the child to finish
    printf("The final value of count is %d\n", *count);

    // Clean up shared memory
    removePeterson();
    shmdt((void *) count);
    shmctl(shmID, IPC_RMID, NULL);

    return 0;
}

void parentProcess(int *count) {
    enterCriticalSection(0);
    // --- Critical Section Start ---
    int temp = *count;
    temp++;
    sleep(rand() % 2);
    *count = temp;
    // --- Critical Section End ---
    exitCriticalSection(0); // <--- 1.3: Parent (process 0) leaves the critical section
}

void childProcess(int *count) {
    enterCriticalSection(1); // <--- 1.4: Child (process 1) enters the critical section
    // --- Critical Section Start ---
    int temp = *count;
    temp--;
    sleep(rand() % 2);
    *count = temp;
    // --- Critical Section End ---
    exitCriticalSection(1);
}