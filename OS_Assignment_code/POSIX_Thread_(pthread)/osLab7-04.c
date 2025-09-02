#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_TASKS 4 
char *messages[NUM_TASKS]; 
void *printHello(void *argv) { 
        sleep(1); 
        int taskID = *((int *)argv); 
        printf("Task %d: %s\n", taskID, messages[taskID]); 
        pthread_exit(0); 
}
void main(int argc, char *argv[]) { 
        pthread_t threads[NUM_TASKS]; 
        int *input;
        int i, t;
        for (i = 0; i < NUM_TASKS; i++) {
                messages[i] = "Hello KMITL";
        }
        for (t = 0; t < NUM_TASKS; t++) {
                input = (int *) malloc(sizeof(int));
                *input = t;
                printf("Create thread %d\n", t);
                pthread_create(&threads[t], 0, printHello, (void *) input);
                pthread_join(threads[t], NULL);
        }
} 