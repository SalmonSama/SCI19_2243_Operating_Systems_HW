char *shm_addr; int isLoop = 1; // Global variables
void SIGHandler(int sig) {
    {
(……….2.1……….) // Signal register
key_t key = ftok(".", 99);
int shm_id = shmget((……….2.2……….));
shm_addr = (char *) shmat(shm_id, NULL, 0);
sprintf(shm_addr, "%d", getpid());
printf("(1) [Server] Writing the server pid = %s
to shared memory ...\n", shm_addr);
while (isLoop); isLoop = 1;
int client_pid = atoi(shm_addr);
printf("(4) [Server] Reading the client pid = %s
from shared memory ...\n", shm_addr);
kill(client_pid, (……….2.3……….)); // Send signal
printf("-\tServer send a signal %d to client ...\n", SIGUSR2);
while (isLoop);
printf("(6) [Server] Reading data \"%s\"\nfrom shared memory ...\n", shm_addr);
shmdt(shm_addr);
(……….2.4……….)
    }