#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "osLab10_myShm.h"

int main() {
    key_t shm_key;
    int shmid;
    Shm_t *shm_ptr;
    char message[SHM_SIZE];

    // Generate a key for the shared memory segment
    shm_key = ftok(SHM_KEY_PATH, SHM_KEY_ID);
    if (shm_key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the shared memory segment (don't create, assume server created it)
    shmid = shmget(shm_key, sizeof(Shm_t), 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process's address space
    shm_ptr = (Shm_t *) shmat(shmid, NULL, 0);
    if (shm_ptr == (Shm_t *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Client: Attached to shared memory at %p\n", shm_ptr);

    // Client loop
    while (1) {
        printf("Client: Enter message (or 'end' to quit): ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = 0; // Remove newline character

        // Wait for server to process previous message or be ready for new data
        while (shm_ptr->server_processed == 0) {
            usleep(100000); // Sleep for 100ms to avoid busy-waiting too much
        }

        // Write PID and message to shared memory
        shm_ptr->pid = getpid();
        strncpy(shm_ptr->buf, message, SHM_SIZE - 1);
        shm_ptr->buf[SHM_SIZE - 1] = '\0'; // Ensure null-termination

        // Signal to server that data is ready and client is waiting
        shm_ptr->server_processed = 0;
        shm_ptr->data_ready = 1;

        if (strcmp(message, "end") == 0) {
            printf("Client: 'end' sent. Exiting.\n");
            break;
        }
    }

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    printf("Client: Detached from shared memory.\n");

    return 0;
}
