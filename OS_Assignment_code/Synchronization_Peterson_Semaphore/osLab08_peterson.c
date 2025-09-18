#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "osLab08_peterson.h" // Assuming the header is named this way

// Pointer to the shared memory segment
static struct Memory *ptr;
// ID of the shared memory segment
static int shmID = 0;

/**
 * @brief Creates and initializes the shared memory for Peterson's algorithm.
 */
void initializePeterson() {
    // Create a private shared memory segment of the size of our struct
    shmID = shmget(IPC_PRIVATE, sizeof(struct Memory), IPC_CREAT | 0666);
    if (shmID < 0) {
        perror("shmget error");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    ptr = (struct Memory *) shmat(shmID, NULL, 0);
    if (ptr == (void *) -1) { // Check for shmat failure
        perror("shmat error");
        exit(1);
    }

    // Initialize the shared variables for the algorithm
    ptr->turn = 0;
    ptr->flag[0] = FALSE;
    ptr->flag[1] = FALSE; // It's important to initialize both flags
}

/**
 * @brief Detaches from and removes the shared memory segment.
 */
void removePeterson() {
    // Detach the shared memory segment
    if (shmdt((void *) ptr) == -1) {
        perror("shmdt error");
    }

    // Mark the segment to be destroyed
    if (shmctl(shmID, IPC_RMID, NULL) == -1) {
        perror("shmctl error");
    }
}

/**
 * @brief The entry protocol for a process wishing to enter its critical section.
 *
 * @param i The ID of the current process (0 or 1).
 */
void enterCriticalSection(int i) {
    int j = 1 - i; // The other process's ID

    // Signal that process 'i' is ready to enter the critical section
    ptr->flag[i] = TRUE;

    // Yield the turn to the other process
    ptr->turn = j;

    // Busy-wait until it is process 'i's turn OR the other process is not ready
    // This loop continues as long as the other process is ready (flag[j] is TRUE)
    // AND it is the other process's turn (turn == j).
    while (ptr->flag[j] && ptr->turn == j);
}

/**
 * @brief The exit protocol for a process leaving its critical section.
 *
 * @param i The ID of the current process (0 or 1).
 * @return Returns 0, typically for success.
 */
int exitCriticalSection(int i) {
    // Signal that process 'i' is no longer in the critical section
    ptr->flag[i] = FALSE;
    return 0;
}