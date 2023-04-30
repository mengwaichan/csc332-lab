/*
Parent_Prcs.c
*****************************************************
Forking a new child to execute Prcs_P1.c and Prcs_P2.c 
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    pid_t child1 = fork();
    int status;

    // Terminate program if forking child1 failed.
    if (child1 < 0)
    {
        printf("Error forking child 1\n");
        return 1;
    }

    // Execute Prcs_P1.c with execv()
    if (child1 == 0)
    {
        char *proc1[] = {"./Prcs_P1", NULL};
        printf("Child 1 Pid : %d\n", getpid());
        sleep(1);
        execv(proc1[0], proc1);
    }
    else
    {   
        // Wait for child1 to end 
        // Fork child2 terminate the program if failed.
        pid_t cpid1 = waitpid(child1, &status, 0);
        pid_t child2 = fork();

        if (child2 < 0)
        {
            printf("Error forking child 1\n");
            return 1;
        }

        // Execute Prcs_P2.c with execv()
        if (child2 == 0)
        {
            wait(NULL);
            char *proc2[] = {"./Prcs_P2", NULL};
            printf("\nChild 2 Pid : %d\n", getpid());
            sleep(1);
            execv(proc2[0], proc2);
        }
    }

    // Wait for all child to end
    wait(NULL);
    printf("Parent Process Ended\n");

    return 0;
}
