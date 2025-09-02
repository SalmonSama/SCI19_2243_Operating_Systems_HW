#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
void main() {
/* ftok to generate unique key */
key_t key = ftok(".", 99);
/* shmget return an identiﬁer in shmid */
int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
/* shmat to attach to shared memory */
char* str = (char*) shmat(shmid, NULL, 0);
/* read original data in shared memory */
printf("Read from mem: %s\n", str);
/* write new data to shared memory */
printf("Data written to mem: %s\n", str);
/* shmdt to detach from shared memory */
shmdt(str);
/* shctl to destroy the shared memory */
shmctl(shmid, IPC_RMID, NULL);
}