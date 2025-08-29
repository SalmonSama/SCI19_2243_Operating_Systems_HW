#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>

void clientProcess(int []);

void main(int argc, char *argv[]) {
	int shm_id;
	int *shm_ptr;
	pid_t pid;
	int status;

	if (argc != 5) {
		printf("Use: %s #1 #2 #3 #4\n", argv[0]);
		exit(1);
	}

	shm_id = shmget(IPC_PRIVATE, 4 * sizeof(int), IPC_CREAT | 0666);
	if (shm_id < 0) {
		printf("*** shmget error (server) ***\n");
		exit(1);
	}
	printf("Server has received a shared memory of four integers ...\n");

	shm_ptr = (int *) shmat(shm_id, NULL, 0);
	if (shm_ptr == NULL) {
		printf("*** shmat error (server) ***");
		exit(1);
	}
	printf("server has attached the sharded memory ...\n");

	shm_ptr[0] = atoi(argv[1]);
	shm_ptr[1] = atoi(argv[2]);
	shm_ptr[2] = atoi(argv[3]);
	shm_ptr[3] = atoi(argv[4]);
	printf("Server has filled %d %d %d %d in shared memory ...\n", shm_ptr[0], shm_ptr[1], shm_ptr[2], shm_ptr[3]);
	printf("Server is about to fork a child process ...\n");
	
	pid = fork();
	if (pid < 0) {
		printf("*** fork error (server) ***\n");
		exit(1);
	} else if (pid == 0) {
		clientProcess(shm_ptr);
		exit(0);
	}
	
	wait(&status);
	printf("Server has detached the completion of its child ...\n");
	shmdt((void *) shm_ptr);
	printf("Server has detached its shared memory ...\n");
	shmctl(shm_id, IPC_RMID, NULL);
	printf("Server has removed its shared memory ...\n");
	printf("Server exits ...\n");
	exit(0);
}

void clientProcess(int share_mem[]) {
	printf("     Client process started\n");
	printf("     Client found %d %d %d %d in shared memory\n", share_mem[0], share_mem[1], share_mem[2], share_mem[3]);
	printf("     CLient is about to exit\n");
}