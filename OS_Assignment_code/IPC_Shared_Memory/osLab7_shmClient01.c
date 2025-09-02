char *shm_addr; int isLoop = 1; // Global variables
void SIGHandler(int sig) {
signal(sig, SIG_IGN);
printf("-\tSIGHandler on client catch a signal %d
from server ...\n", sig);
isLoop = 0; signal(sig, SIGHandler); // Signal register
}
void main() {
signal(SIGUSR2, SIGHandler); // Signal register
key_t key = (……….2.5……….)
int shm_id = shmget((……….2.6……….));
shm_addr = (char *) shmat(shm_id, NULL, 0);
int server_pid = atoi(shm_addr);
printf("(2) [Client] Reading the server pid = %s
from shared memory ...\n", shm_addr);
sprintf(shm_addr, "%d", getpid());
printf("(3) [Client] Writing the client pid = %s
to shared memory ...\n", shm_addr);
kill(server_pid, (……….2.7……….)); // Send signal
printf("-\tClient send a signal %d to server ...\n", SIGUSR1);
while (isLoop);
sprintf(shm_addr, "%s", "CS KMITL");
printf("(5) [Client] Writing data \"%s\"
to shared memory ...\n", shm_addr);
kill(server_pid, (……….2.8……….)); // Send signal
printf("-\tClient send a signal %d to server ...\n", SIGUSR1);
(……….2.9……….)
}