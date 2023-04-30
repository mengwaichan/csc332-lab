#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){

    char* filepath = argv[1];
    int returnval;

    returnval = access(filepath, F_OK);
    if(returnval == -1){
        if (errno == ENOENT)
            printf("%s does not exist \n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 1;
    }

    int fd = open(filepath, O_RDONLY);

    if(fd == -1){
        printf("\n%s does not have read permission\n", filepath);
        return 1;
    }

    char buf[1];
    while(read(fd, &buf, 1))
        printf("%s", buf);

    printf("\n");
    
    close(fd);
    return 0;
}