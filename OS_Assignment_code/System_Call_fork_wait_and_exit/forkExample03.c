#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
        pid_t id;
        printf("<pid: %d>\n\n", getpid());
        id = fork();
        if (id < 0) {
                fprintf(stderr, "fork() failed\n");
        } else if (id == 0) {
                printf("I'm child\tfork return id = %d\t<pid: %d>\n", id, getpid());
        } else {
                printf("I'm parent\tfork return id = %d\t<pid: %d>\n", id, getpid());
        }
        return 0;
} 