#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]){
    
    char* filepath = argv[1];
    int returnval;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf("\n%s exists\n", filepath);
    else {
        if (errno == ENOENT)
            printf("%s does not exist \n", filepath);
        else if (errno == EACCES)
            printf("%s is not accessible\n", filepath);
        return 0;
    }
    
    // Check read access
    returnval = access(filepath, R_OK);
    if (returnval == 0)
        printf("\n%s has read permission \n", filepath);
    else 
        printf("\n%s has no read permission\n", filepath);

    // Check write access
    returnval = access(filepath, W_OK);
    if (returnval == 0)
        printf("\n%s has write permission \n", filepath);
    else 
        printf("\n%s has no write permission\n", filepath);

    return 0;
}