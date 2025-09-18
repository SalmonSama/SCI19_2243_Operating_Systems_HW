#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NITER 100000

pthread_attr_t attr[2];
pthread_t tid[2];
sem_t mySemaphore;
int cnt;

void * Count(void* a) {
    int i;
    for (i = 0; i < NITER; i++) {
        sem_wait(&mySemaphore); // <--- 2.8: Wait for/acquire the semaphore lock
        cnt++;
        sem_post(&mySemaphore); // Release the semaphore lock
    }

    void* lastSeen = malloc(sizeof(int));
    if (lastSeen == NULL) pthread_exit(NULL); // Check malloc success

    // This block only runs for the first thread (tid[0])
    if (pthread_self() == tid[0]) {
        *(int *)lastSeen = cnt;
        printf("thr %lu exits. lastSeen = %d\n", pthread_self(), *(int *)lastSeen);
        pthread_exit((void*)lastSeen);
    }
    
    // The second thread will exit implicitly here
    return NULL;
}

int main() {
    sem_init(&mySemaphore, 0, 1); // <--- 2.9: Initialize semaphore with value 1

    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);

    pthread_create(&tid[0], &attr[0], Count, NULL);
    pthread_create(&tid[1], &attr[1], Count, NULL);

    void* returnVal;
    pthread_join(tid[0], &returnVal); // Wait for the first thread

    int x = *(int*)returnVal;
    printf("Last cnt from tid[0] is %d\n", x);
    free(returnVal); // Free the memory allocated in the thread

    pthread_join(tid[1], NULL); // Wait for the second thread

    printf("final cnt = %d\n", cnt);

    sem_destroy(&mySemaphore);
    return 0;
}