/*
Prcs_P2.c
*****************************************************
Open sourcefile, destination1.txt and destination2.txt copy contexts from sourcefile 
to destination1.txt and destination2.txt
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int checkAccess(char *fileName)
{
    int returnval;

    // Check access for file
    returnval = access(fileName, F_OK);
    if (returnval == 0)
        printf("%s exists\n", fileName);
    else
    {
        if (errno == ENOENT)
            printf("%s does not exist \n", fileName);
        else if (errno == EACCES)
            printf("%s is not accessible\n", fileName);
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *sourcefile = "source.txt", *dest1 = "destination1.txt", *dest2 = "destination2.txt";

    int returnval;

    if (checkAccess(sourcefile))
        return 1;

    if (checkAccess(dest1))
        return 1;

    if (checkAccess(dest2))
        return 1;
    int fd_source = open(sourcefile, O_RDONLY);
    int fd_dest1 = open(dest1, O_RDWR);
    int fd_dest2 = open(dest2, O_RDWR);

    if (fd_source == -1)
    {
        printf("\nError reading %s\n", sourcefile);
        return 1;
    }
    if (fd_dest1 == -1)
    {
        printf("\nError writing %s\n", dest1);
        return 1;
    }
    if (fd_dest2 == -1)
    {
        printf("\nError writing %s\n", dest2);
        return 1;
    }

    char buf;
    int count = 1;

    while (read(fd_source, &buf, 1))
    {

        if (count <= 100)
            if (buf == '1')
                write(fd_dest1, "L", 1);
            else
                write(fd_dest1, &buf, 1);

        if (count > 100 && count <= 150)
            if (buf == '3')
                write(fd_dest2, "E", 1);
            else
                write(fd_dest2, &buf, 1);

        if (count == 150)
            count = 0;

        count++;
    }
    printf("\nCopied text from source.txt to destination1.txt\n");
    printf("Copied text from source.txt to destination2.txt\n");

    close(fd_source);
    close(fd_dest1);
    close(fd_dest2);

    return 0;
}