#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
     pid_t id, sub_id;
        int i, j;
        printf("Only parent before fork\n");
        for (i = 0; i < 5; i++) {
                id = fork();
                if (id == 0) {
                        if ((i % 2) == 0) {
                                printf("I'm child no.%d\n", i);
                                int num_gc = i;
                                for (j = 0; j < num_gc; j++) {
                                        sub_id = fork();
                                        if (sub_id == 0) {
                                           printf("I'm gc num:%d of even child no.%d\n", j, i);
                                           exit(0);
                                        }
                                }
                                while(wait(NULL) != -1);
                                exit(0);
                        } else {
                                printf("I'm child no.%d\n", i);
                                int num_gc = i * 2;
                                for (j = 0; j < num_gc; j++) {
                                        sub_id = fork();
                                        if (sub_id == 0) {
                                           printf("I'm gc num:%d of odd child no.%d\n", j, i);
                                           exit(0);
                                        }
                                }
                                while(wait(NULL) != -1);
                                exit(0);
                        }
                }
        }
        while(wait(NULL) != -1);
        return 0;
}