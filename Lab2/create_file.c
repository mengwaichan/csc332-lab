#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]){

    char* filepath = argv[1];
    int returnval;

    int fd = open(filepath, O_RDONLY|O_CREAT);
   
    if(fd == -1){
        printf("\nCannot open %s\n", filepath);
        return 1;
    }
    else{
        printf("\n Open %s successful\n", filepath);
    }

    close(fd);
    return 0;
}