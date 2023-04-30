#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    pid_t child1 = fork();
    int status;

    if (child1 < 0)
    {
        printf("Error forking child one.\n");
        return 1;
    }

    if (child1 == 0)
    {
        printf("I am child one, my pid is %d\n", getpid());
    }
    else
    {
        pid_t child2 = fork();
        if (child2 < 0)
        {
            printf("Error forking child two.\n");
            return 1;
        }
        else if (child2 == 0)
        {
            printf("I am child two, my pid is %d\n", getpid());
        }
        else
        {   
            // Parent process wait for both child process to finish before preceeding
            pid_t cpid1 = waitpid(child1, &status, 0);
            pid_t cpid2 = waitpid(child2, &status, 0);

            printf("Child one ended, pid : %d\n", child1);
            printf("Child two ended, pid : %d\n", child2);

            printf("I am Parent, pid: %d\n", getpid());
        }
    }
    return 0;
}