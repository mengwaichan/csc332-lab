#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int checkAccess(char *fileName)
{
    int returnval;

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
    char *file = argv[1];

    pid_t pipefd[2], child;

    int status, fd;
    char buf[1];
    int size;

    if (checkAccess(file))
        return 1;
    fd = open(file, O_RDWR);

    if (fd == 1)
    {
        printf("error opening file.\n");
        return 1;
    }
    else
        printf("Opened %s.\n", file);

    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);


    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    child = fork();

    if (child == -1)
    {
        perror("fork");
        return 1;
    }

    if (child == 0)
    {

        printf("Child is reading from file to pipe[1]\n");
        while (read(fd, &buf, 1))
        {
            write(pipefd[1], buf, 1);
        }

        close(pipefd[1]);
        printf("pipe[1] closed\n");
    }
    else
    {
   
        pid_t cpid = waitpid(child, &status, 0);
        char msg[size];

 
        printf("Parent is writing from pipe[0] to file\n");
        write(fd, "\nParent is writing: ", 20);
        read(pipefd[0], &msg, size);
        write(fd, &msg, size);

        close(pipefd[0]);
        printf("pipe[0] closed\n");
        close(fd);
        printf("file closed\n");
    }

    return 0;
}