#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void SIGhandler(int sig) {
    switch (sig) {
        case SIGINT:
            printf("Ha Ha Ha ... you can not interrupt me ;P\n");
            break;
        case SIGQUIT:
            printf("Ha Ha Ha ... you can not quit me ;P\n");
            break;
    }
}

int main(void) {
    /* Register Quit handler */
    if (signal(SIGQUIT, SIGhandler) == SIG_ERR) {
        printf("\ncan't catch SIGQUIT\n");
    }
    /* Register Interrupt handler */
    if (signal(SIGINT, SIGhandler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
    }
    
    printf("Running... Press Ctrl-C or Ctrl-\\ to send signals.\n");
    printf("Use 'kill -9 %d' to terminate this process.\n", getpid());

    while(1) {
        sleep(1);
    }
    
    return 0;
}