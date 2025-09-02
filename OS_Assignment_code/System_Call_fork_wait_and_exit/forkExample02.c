#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
 
int main() { 
        int i = 0; 
        pid_t id = fork(); 
        if (id > 0) { 
                i += 1; 
                printf("I'm parent\t i = %d\n", i); 
        } else { 
                i += 2; 
                printf("I'm child\t i = %d\n\n", i); 
        } 
        return 0; 
}