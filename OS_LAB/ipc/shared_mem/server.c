#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include "shm_status.h"

void main(int argc, char *argv[]) {
	key_t shm_key;
	int shm_id;
	struct Memory *shm_ptr;

	shm_key = ftok(".", 'x');
	shm_id = shmget(shm_key, sizeof(struct Memory), 0666);
	if (shm_id < 0) {
		printf("*** shmget error ***\n");
		exit(1);
	}
	printf("Server has received a shared memory of four integers ...\n");

	shm_ptr = (struct Memory *) shmat(shm_id, NULL, 0);
	if (shm_ptr == NULL) {
		printf("*** shmat error ***\n");
		exit(1);
	}
	printf("Server has attached the shared memory ...\n");

	shm_ptr->status = NOT_READY;
	shm_ptr->data[0] = atoi(argv[1]);
	shm_ptr->data[1] = atoi(argv[2]);
	shm_ptr->data[2] = atoi(argv[3]);
	shm_ptr->data[3] = atoi(argv[4]);
	printf("Server has filled %d %d %d %d to shared memory ...\n", shm_ptr->data[0], shm_ptr->data[1], shm_ptr->data[2], shm_ptr->data[3]);
	shm_ptr->status = FILLED;

	printf("Please start the client in another window ...\n");
	
	while (shm_ptr->status != TAKEN) {
		sleep(1);
	}
	
	printf("Server has detected the completion of its child ...\n");
	shmdt((void *) shm_ptr);
	printf("Server has deteached its shared memory ...\n");
	shmctl(shm_id, IPC_RMID, NULL);
	printf("Server has removed its shread memory ...\n");
	printf("Server exits ...\n");
	exit(0);
} 