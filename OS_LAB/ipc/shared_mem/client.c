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
         printf("\tClient has received a shared memory of four integers ...\n");
 
         shm_ptr = (struct Memory *) shmat(shm_id, NULL, 0);
         if (shm_ptr == NULL) {
                 printf("*** shmat error ***\n");
                 exit(1);
	}
	printf("\tClient has attached the shared memory ...\n");
	
	while (shm_ptr->status != FILLED);
	printf("\tClient found the data is ready ...\n");
	printf("\tClient found %d %d %d %d in shared memory ...\n", shm_ptr->data[0], shm_ptr->data[1], shm_ptr->data[2], shm_ptr->data[3]);

	shm_ptr->status = TAKEN;
	printf("\tClient has informed server data have been taken ...\n");
	shmdt((void *) shm_ptr);
	printf("\tClient has detached its shared memory ...\n");
	printf("\tClient exits ...\n");
	exit(0);
}