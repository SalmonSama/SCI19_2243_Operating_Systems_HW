#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
 
int main() { 
        pid_t id; 
        int num = 10; 
        int i; 
        for (i = 0; i < 3; i++) { 
                id = fork(); 
                if (id == 0) { 
                        printf("I'm Child, i = %d\n", i); 
                        exit(0); 
                        printf("Should not be executed\n"); 
                } 
        } 
        while(wait(NULL) != -1); 
        printf("Parent number = %d\n", num); 
        return 0; 
}