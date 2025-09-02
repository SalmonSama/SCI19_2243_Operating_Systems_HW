#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 1024

void main() {
    int pid, nread, pfd1[2], pfd2[2];
    char buf[SIZE];
    if (pipe(pfd1) == -1) { // Create pipe#1
        perror("pipe failed");
        exit(1);
    }
    if (pipe(pfd2) == -1) { // Create pipe#2
        perror("pipe failed");
        exit(1);
    }
    if ((pid = fork()) < 0) { // Fork process
        perror("fork failed");
        exit(2);
    }
    if (pid == 0) { // child process
        /* Close pipe#1 to write and pipe#2 to read */
        close(pfd1[1]);
        close(pfd2[0]);
        /* Pipe Receive */
        while ((nread = read(pfd1[0], buf, SIZE)) != 0) {
            printf("Child read:\t %s\n", buf);
        }
        close(pfd1[0]);
        /* Pipe Send */
        strcpy(buf, "I am fine thank you :)");
        write(pfd2[1], buf, strlen(buf) + 1);
        close(pfd2[1]);
    } else { // parent process
        /* Close pipe#1 to read and pipe#2 to write */
        close(pfd1[0]);
        close(pfd2[1]);
        /* Pipe Send */
        strcpy(buf, "How are you ?");
        write(pfd1[1], buf, strlen(buf) + 1);
        close(pfd1[1]);
        /* Pipe Receive */
        while ((nread = read(pfd2[0], buf, SIZE)) != 0) {
            printf("Parent read:\t %s\n", buf);
        }
        close(pfd2[0]);
    }
}
