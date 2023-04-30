#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int checkAccess(char* fileName){
    int returnval;

    // Check access for file
    returnval = access (fileName, F_OK);
    if (returnval == 0)
        printf("\n%s exists\n", fileName);
    else {
        if (errno == ENOENT)
            printf("%s does not exist \n", fileName);
        else if (errno == EACCES)
            printf("%s is not accessible\n", fileName);
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]){
    
    char *sourcefile = argv[1], *destinationfile = argv[2];
    int returnval;

    if(checkAccess(sourcefile))
        return 1;

    if(checkAccess(destinationfile))
        return 1;

    int fd_source = open(sourcefile, O_RDONLY);
    int fd_dest = open(destinationfile, O_RDWR);

    if(fd_source == -1){
        printf("\nError reading %s\n", sourcefile);
        return 1;
    }
    if(fd_dest == -1){
        printf("\nError writing %s\n", destinationfile);
        return 1;
    }

    char buf;
    int count = 1;
    
    while(read(fd_source, &buf, 1)){
        
        if(buf == '1')
            write(fd_dest, "L", 1);
        else
            write(fd_dest, &buf, 1);
    
        if(count == 100){
            write(fd_dest, "XYZ", strlen("XYZ"));
            count = 1;
        }
        count++;
    }
    printf("\nCopied text from source.txt to destination.txt\n");

    close(fd_source);
    close(fd_dest);

    return 0;

}