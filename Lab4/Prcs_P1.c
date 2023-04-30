/*
Prcs_P1.c
*****************************************************
Create and Open destination1.txt and destination2.txt
with Read and Write Permission
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

    char *file1 = "destination1.txt";
    char *file2 = "destination2.txt";

    int fd1 = open(file1, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH);
    int fd2 = open(file2, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH);

    if (fd1 == -1)
    {
        printf("Cannot open %s\n", file1);
        return 1;
    }
    else
    {
        printf("Open %s successful\n", file1);
    }

    if (fd2 == -1)
    {
        printf("Cannot open %s\n", file2);
        return 1;
    }
    else
    {
        printf("Open %s successful\n", file2);
    }

    close(fd1);
    close(fd2);

    return 0;
}