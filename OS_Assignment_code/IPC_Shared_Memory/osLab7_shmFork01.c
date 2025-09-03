#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void main() {
    int *count, shm_id;
    /* get identiﬁer of shared memory in shm_id */
    //shm_id = shmget(key, sizeof(int), 0666 | IPC_CREAT);
    shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    /* shmat to attach to shared memory */
    if (shm_id < 0) {
        perror("shmget");
        exit(1);
    }
    count = (int*) shmat(shm_id, NULL, 0);
    if (count == (int*) -1) {
        perror("shmat");
        exit(1);
    }

    count[0] = 100; 

    if (fork() == 0) { // Child Process
        int temp = count[0];
        sleep(1);
        temp -= 1;
        count[0] = temp;
        printf("Child decrements value. Current value: %d\n", count[0]);
        exit(0);
    }
    
    // Parent Process
    wait(NULL);
    
    int temp = count[0];
    sleep(1);
    temp += 1;
    count[0] = temp;
    printf("Parent increments value. Current value: %d\n", count[0]);

    sleep(1);
    printf("Final answer is %d\n", count[0]);
    /* shmdt to detach from shared memory */
    shmdt(count);
    /* shmctl to destroy the shared memory */
    shmctl(shm_id, IPC_RMID, NULL);
}
