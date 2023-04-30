#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    pid_t child = fork();
    int status;
    char* arg[]={"ls", "-laFRh", NULL};

    if(child < 0){
        printf("Error forking child. ");
        return 1;
    }
    if(child == 0){
        printf("\nForking child successful.\n");
        printf("Child Pid = %d\n\n", getpid());
        if(execvp(arg[0], arg) < 0){
            printf("Error execvp()\n");
            return 1;
        }
    }
    else {
        pid_t cpid = waitpid(child, &status, 0);
        printf("\nParent Process ended\n");
    }
    return 0;
}