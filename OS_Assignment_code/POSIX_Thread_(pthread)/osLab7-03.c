#include <pthread.h>
#include <stdio.h>

static int input = 999; 
void *myfunc(void *argv) {
        int value = *((int *)argv);
        printf("From thread process ...\n");
        printf("Thread value: %d\n", value);
        pthread_exit(NULL);
}
pthread_t launch_thread(void) {
        input += 1;
        pthread_t tid;
        pthread_attr_t tattr;
        pthread_attr_init(&tattr);
        pthread_create(&tid, &tattr, myfunc, &input);
        return tid;
}
void main(void) {
        pthread_t tid = launch_thread();
        pthread_join(tid, NULL);
        printf("From main process ...\n");
}