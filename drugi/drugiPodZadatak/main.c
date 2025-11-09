#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv){
    setbuf(stdout, NULL);
    int n = atoi(argv[1]);
    int wstatus;

    for(int i = 0; i < n; i++) {
        pid_t pid = fork();
        if(pid != 0){
            printf("Roditelj %d\n", i);
            wait(NULL);
            //waitpid(pid, &wstatus, 0);
        } 
        else {
            printf("Dijete %d\n", i);
            exit(0);
        }
    }
    return 0;
} 
