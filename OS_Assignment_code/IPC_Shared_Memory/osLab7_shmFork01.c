#include <sys/ipc.h>
#include <sys/shm.h>
void main() {
int *count, shm_id;
/* get identiﬁer of shared memory in shm_id */
//shm_id = shmget(key, sizeof(int), 0666 | IPC_CREAT);
//shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
/* shmat to attach to shared memory */
count = (……….1.2……….) shmat(shm_id, NULL, 0);
count[0] = 100; // initial value
if (fork() == 0) {
int temp = count[0]; sleep(1);
temp -= 1; count[0] = temp;
printf("Child decrements value at %p\n", &count);
exit(0);
}
wait(NULL);
int temp = count[0]; sleep(1);
temp += 1; count[0] = temp;
printf("Parent increments value at %p\n", &count);
sleep(3); printf("ﬁnal anwser is %d\n", count[0]);
/* shmdt to detach from shared memory */
(……….1.3……….)
/* shmctl to destroy the shared memory */
shmctl(shm_id, (……….1.4……….), NULL);
}