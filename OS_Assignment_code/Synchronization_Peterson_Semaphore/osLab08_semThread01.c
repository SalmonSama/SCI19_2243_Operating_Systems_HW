#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int count = 100;
sem_t mutex;

void *increment(void *param);
void *decrement(void *param); // <--- 2.1: Prototype for the decrement function

int main() {
    pthread_t tid1, tid2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    // Initialize the semaphore for use between threads (pshared = 0)
    sem_init(&mutex, 0, 1); // <--- 2.2: 0 indicates semaphore is for threads

    // Create two threads
    pthread_create(&tid1, &attr, increment, NULL);
    pthread_create(&tid2, &attr, decrement, NULL);

    // Wait for both threads to complete their execution
    pthread_join(tid1, NULL); // <--- 2.3: Wait for the first thread to exit
    pthread_join(tid2, NULL);

    printf("count = %d\n", count);

    // Clean up and destroy the semaphore
    sem_destroy(&mutex); // <--- 2.4: Pass the address of the semaphore
    return 0;
}

// Thread function to increment the global count
void *increment(void *param) {
    int temp;
    sem_wait(&mutex); // Lock
    // --- Critical Section Start ---
    temp = count;
    sleep(rand() % 5);
    temp += 1;
    count = temp;
    // --- Critical Section End ---
    sem_post(&mutex); // Unlock
    pthread_exit(0);
}

// Thread function to decrement the global count
void *decrement(void *param) { // <--- 2.5: Definition of the decrement function
    int temp;
    sem_wait(&mutex); // Lock
    // --- Critical Section Start ---
    temp = count;
    sleep(rand() % 5);
    temp -= 1;
    count = temp;
    // --- Critical Section End ---
    sem_post(&mutex); // Unlock
    pthread_exit(0);
}