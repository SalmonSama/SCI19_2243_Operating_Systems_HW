#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct mydata {
        double d;
        int i;
} data;
void *myfunc(void *argv) {
        data *my = (data *)malloc(sizeof(data));
        my->d = 3.14;
        my->i = 40;
        pthread_exit(my);
}
void main() {
        pthread_t tid;
        data my;
        void *retval;
        pthread_create(&tid, NULL, myfunc, NULL);
        pthread_join(tid, &retval);
        my = *((data *)retval);
        free(retval);
        printf("%f, %d\n", my.d, my.i);
}
