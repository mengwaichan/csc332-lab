#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{   
    // coverting argv to integer
    int num = atoi(argv[1]);

    pid_t child1, child2;
    int status;

    child1 = fork();

    if (child1 == 0)
    {   
        // Child1 calculate S1, S1 = sum of all odd number
        int sum = 0;
        for (int i = 1; i <= num; i += 2)
        {
            sum += i;
        }
        printf("S1 = %d, pid = %d\n", sum, getpid());
    }
    else
    {
        child2 = fork();

        if (child2 == 0)
        {
            // Child2 calculate S2, S2 = sum of all even number
            int sum = 0;
            for (int i = 0; i <= num; i += 2)
            {
                sum += i;
            }
            printf("S2 = %d, pid = %d\n", sum, getpid());
        }
        else
        {   
            // Parent Process wait for child1 and child2 to halt, then get the sum of all number
            pid_t cpid1 = waitpid(child1, &status, 0);
            pid_t cpid2 = waitpid(child2, &status, 0);
            
            int sum;
            for (int i = 0; i <= num; i++)
            {
                sum += i;
            }
            printf("S3 = %d, pid = %d\n", sum, getpid());
        }
    }

    return 0;
}