#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void SIGhandler(int sig);

int main(void) {
    /* Register Quit handler */
    if (signal(SIGQUIT, SIGhandler) == SIG_ERR) {
        printf("\ncan't catch SIGQUIT\n");
    }
    /* Register Interrupt handler */
    if (signal(SIGINT, SIGhandler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
    }
    while (1) {
        sleep(1);
    }
    return (0);
}

void SIGhandler(int sig) {
    switch (sig) {
    case 2:
        printf("Ha Ha Ha ... you can not interrupt me ;P\n");
        break;
    case 3:
        printf("Ha Ha Ha ... you can not quit me ;P\n");
    }
}
