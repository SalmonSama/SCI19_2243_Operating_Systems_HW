#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
int main() { 
pid_t id; 
int i = 0; 
id = fork(); 
if (id > 0) { 
//              wait(NULL); 
i += 1; 
printf("I'm parent, i = %d\n", i); 
} else { 
i += 2; 
printf("I'm child, i = %d\n", i); 
//              exit(0); 
} 
printf("my i = %d\n", i); 
return 0; 
} 