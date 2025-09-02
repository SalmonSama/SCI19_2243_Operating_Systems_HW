void main(int argc, char *argv[]) {
int shm_id, *shm_addr;
pid_t pid;
if (argc != 5) {
printf("Use: %s #1 #2 #3 #4\n", argv[0]); exit(1);
}
shm_id = (……….1.6……….)
if (shm_id < 0) {
printf("*** shmget error (server) ***\n"); exit(1);
}
printf("Server has received a shared memory of four integers ...\n");
shm_addr = (……….1.7……….)
if (shm_addr == NULL) {
printf("*** shmat error (server) ***\n"); exit(1);
}
printf("Server has attached the shared memory ...\n");
/* Set value from argv to shared memory */
shm_addr[0] = (……….1.8……….) (argv[1]);
shm_addr[1] = (……….1.8……….) (argv[2]);
shm_addr[2] = (……….1.8……….) (argv[3]);
shm_addr[3] = (……….1.8……….) (argv[4]);
printf("Server has ﬁlled %d %d %d %d in shared memory ...\n",
shm_addr[0], shm_addr[1], shm_addr[2], shm_addr[3]);
printf("Server is about to fork a child process ...\n");
if ((pid = fork()) < 0) {
printf("*** fork error (server) ***\n"); exit(1);
} else if (pid == 0) {
    clientProcess((……….1.9……….)); exit(0);
} else {
wait(NULL);
printf("Server has detected the completion of its child ...\n");
shmdt((void *) shm_addr);
printf("Server has detached its shared memory ...\n");
(……….1.10……….)
printf("Server has removed its shared memory ...\n");
printf("Server exits ...\n");
}
}
void clientProcess(int shm_addr[]) {
printf("\tClient process started\n");
printf("\tClient found %d %d %d %d in shared memory\n",
shm_addr[0], shm_addr[1], shm_addr[2], shm_addr[3]);
printf("\tClient is about to exit\n");
}