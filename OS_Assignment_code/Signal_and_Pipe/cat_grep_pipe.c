#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int     pfd[2];
    pid_t   pid;

    if (pipe(pfd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        execlp("cat", "cat", "/etc/passwd", NULL);
        perror("execlp 'cat' failed");
        exit(EXIT_FAILURE);
    }
    else {
        close(pfd[1]);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        execlp("grep", "grep", "^root", NULL);
        perror("execlp 'grep' failed");
        exit(EXIT_FAILURE);
    }

    wait(NULL);

    return 0;
}