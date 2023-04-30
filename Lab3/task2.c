#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{

    int a = 10, b = 25, fq = 0, fr = 0;

    fq = fork();

    if (fq == 0)
    {   // Child Process Q
        // a = 35, b = 25
        a = a + b;
        printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());

        fr = fork();

        if (fr == 0)
        {   // Child process R
            // a = 35, b = 45
            b = b + 20;
            printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
        }
        else
        {   // a = 905, b = 25
            a = (a * b) + 30;
            printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
        }
    }
    else
    {   // Parenet process 
        // a = 10, b = 30
        b = a + b - 5;
        printf("a = %d, b = %d, process_id = %d\n", a, b, getpid());
    }

    wait(NULL);
    return 0;
}