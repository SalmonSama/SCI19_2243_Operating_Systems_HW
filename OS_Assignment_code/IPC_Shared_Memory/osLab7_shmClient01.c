#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

char *shm_addr; 
int isLoop = 1; // Global variables

void SIGHandler(int sig) {
    signal(sig, SIG_IGN);
    printf("-\tSIGHandler on client catch a signal %d from server ...\n", sig);
    isLoop = 0;
    signal(sig, SIGHandler); // Signal register
}

int main(void) {
    signal(SIGUSR2, SIGHandler); // Signal register 

    key_t key = ftok(".", 99);

    int shm_id = shmget(key, 1024, 0666);
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }

    shm_addr = (char *) shmat(shm_id, NULL, 0);
    if (shm_addr == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    int server_pid = atoi(shm_addr);
    printf("(2) [Client] Reading the server pid = %s from shared memory ...\n", shm_addr);

    sprintf(shm_addr, "%d", getpid());
    printf("(3) [Client] Writing the client pid = %s to shared memory ...\n", shm_addr);

    kill(server_pid, SIGUSR1);
    printf("-\tClient send a signal %d to server ...\n", SIGUSR1);

    while (isLoop);  
    isLoop = 1;

    sprintf(shm_addr, "%s", "CS KMITL");
    printf("(5) [Client] Writing data \"%s\" to shared memory ...\n", shm_addr);

    kill(server_pid, SIGUSR1);
    printf("-\tClient send a signal %d to server ...\n", SIGUSR1);

    shmdt(shm_addr);

    return 0;
}
