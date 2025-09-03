#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define SIZE 10

void main() {
    int nread, pfd[2];
    char read_buf[SIZE], write_buf[SIZE * 100];
    if ((pipe(pfd)) == -1) {    // Create pipe
        perror("pipe failed\n");
        exit(-1);
    }
    if (fork() == 0) { // Child Process
        close(pfd[1]); // Close to write (output)
        int cnt = 0;
        while ((nread = read(pfd[0], read_buf, SIZE)) != 0) {
            read_buf[nread] = '\0';
            printf("Child read at round %d: %s\n", cnt+=1, read_buf);
        }
        close(pfd[0]);
    } else { // Parent Process 
        close(pfd[0]);// Close to read (input)

        strcpy(write_buf, "Hello ... CS ... SUT ... ARE YOU HAPPY?");
        write(pfd[1], write_buf, strlen(write_buf) + 1);
        close(pfd[1]);
        printf("Parent write done !!!\n");
        wait(0); // Wait to sync return prompt when exit program
    }
}