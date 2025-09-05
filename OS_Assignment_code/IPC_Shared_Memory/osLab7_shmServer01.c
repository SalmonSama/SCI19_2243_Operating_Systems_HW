#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *shm_addr; 
int isLoop = 1; // Global variables

void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    printf("-\tSIGHandler on server catch a signal %d from client ...\n", sig);
    isLoop = 0;
    signal(sig, SIGHandler); // Signal register
}

int main(void) {
    // Signal register
    signal(SIGUSR1, SIGHandler);
    signal(SIGUSR2, SIGHandler);

    key_t key = ftok(".", 99);

    // shmget arguments
    int shm_id = shmget(key, 1024, IPC_CREAT | 0666);

    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    shm_addr = (char *) shmat(shm_id, NULL, 0);
    if (shm_addr == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    sprintf(shm_addr, "%d", getpid());
    printf("(1) [Server] Writing the server pid = %s to shared memory ...\n", shm_addr);

    while (isLoop); 
    isLoop = 1;

    int client_pid = atoi(shm_addr);
    printf("(4) [Server] Reading the client pid = %s from shared memory ...\n", shm_addr);

    // Send signal to client
    kill(client_pid, SIGUSR2);
    printf("-\tServer send a signal %d to client ...\n", SIGUSR2);

    while (isLoop);

    printf("(6) [Server] Reading data \"%s\" from shared memory ...\n", shm_addr);

    shmdt(shm_addr);

    // remove shared memory
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
