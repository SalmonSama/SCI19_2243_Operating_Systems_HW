#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "osLab08_peterson.h" // Assuming this is the correct header name

// Function prototypes
void childProcess(int *);
void parentProcess(int *);

int main(int argc, char *argv[]) {
    int shmID_count, status;
    int *count;
    pid_t pid;

    // Create a shared memory segment for the 'count' variable
    shmID_count = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    if (shmID_count < 0) {
        perror("shmget error for count");
        exit(1);
    }

    // Attach the shared memory segment for 'count'
    count = (int *) shmat(shmID_count, NULL, 0);
    if (count == (void *) -1) {
        perror("shmat error for count");
        exit(1);
    }

    *count = 5; // Initialize the shared counter
    printf("Initial value of count is %d\n", *count);

    // Initialize the separate shared memory used by Peterson's algorithm
    initializePeterson();

    // Create a child process
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        // This is the child process
        childProcess(count);
        exit(0); // Child process terminates
    }

    // This is the parent process
    parentProcess(count);

    // Parent waits for the child to complete
    wait(&status);

    printf("The final value of count is %d\n", *count);

    // Clean up Peterson's shared memory
    removePeterson();

    // Clean up the 'count' shared memory
    shmdt((void *) count);
    shmctl(shmID_count, IPC_RMID, NULL);

    return 0;
}

/**
 * @brief Parent process logic. It increments the shared count.
 * @param count Pointer to the shared integer.
 */
void parentProcess(int *count) {
    // Process 0 enters its critical section
    enterCriticalSection(0);

    // --- Start of Critical Section ---
    printf("Parent (PID: %d) entered critical section. Count = %d\n", getpid(), *count);
    int temp = *count;
    temp++;
    sleep(rand() % 2); // Simulate some work
    *count = temp;
    printf("Parent (PID: %d) leaving critical section. Count = %d\n", getpid(), *count);
    // --- End of Critical Section ---

    exitCriticalSection(0);
}

/**
 * @brief Child process logic. It decrements the shared count.
 * @param count Pointer to the shared integer.
 */
void childProcess(int *count) {
    // Process 1 enters its critical section
    enterCriticalSection(1);

    // --- Start of Critical Section ---
    printf("Child  (PID: %d) entered critical section. Count = %d\n", getpid(), *count);
    int temp = *count;
    temp--;
    sleep(rand() % 2); // Simulate some work
    *count = temp;
    printf("Child  (PID: %d) leaving critical section. Count = %d\n", getpid(), *count);
    // --- End of Critical Section ---

    exitCriticalSection(1);
}