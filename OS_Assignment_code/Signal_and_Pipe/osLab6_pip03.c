#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
    int pid, pfd[2];
    if ((pipe(pfd) == -1)) {    // Create pipe
        perror("pipe failed"); exit(1);
    }

    if ((pid = fork()) < 0) {   // Fork proces
        perror("fork failed"); exit(2);
    } else if (pid == 0) {  // Child process

        close(pfd[0]);  // Close pipe input

        dup2(pfd[1], 1);    // Duplicate pipe output for exec()

        close(pfd[1]);  // Close pipe output

        execlp("ls", "ls", NULL);   // Exec ls program

        perror("ls failed"); exit(3);

    } else {    // Parent process

        close(pfd[1]);  // Close pipe output

        dup2(pfd[0], 0);    // Duplicate pipe input for exec()

        close(pfd[0]);  // Close pip input

        execlp("wc", "wc", NULL);   // Exec wc program

        perror("wc failed"); exit(4);
    }
    exit(0);    // End program
    /* Parent process wait child process sync by OS */
}