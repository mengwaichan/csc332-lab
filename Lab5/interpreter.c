#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

// Coverting the user input into String array
void to_argv(char* input, char* cmd[]){ 
    int i = 0;
    int arg = 0;

    do
    {
        while(input[i] == ' ' || input[i] == '\0')
            i++;
        
        if(input[i] == '\n')
            break;

        cmd[i] = &input[i];

        while (input[i] != ' ' && input[i] != '\n')
            i++;

        if(input[i] == '\n'){
            input[i] = '\0';
            arg++;
            break;
        }

        input[i] = '\0';
        arg++;
        
    } while (1);

    cmd[i] = (char *)NULL;
    return;
    
}

int main(int argc, char* argv[]){

    size_t SIZE = 200;
    char* input = malloc(SIZE * sizeof(char));
    char* cmd[10];

    do{
        printf("Command: ");
        fflush(stdout);

        // Get user input and covert it to a string array
        getline(&input, &SIZE, stdin);
        to_argv(input, cmd);

        // Check if the first input is "exit", "EXIT", "Exit"
        if(strcmp(cmd[0], "Exit") == 0 || strcmp(cmd[0], "exit") == 0 | strcmp(cmd[0], "EXIT") == 0){
            printf("Interpreter Terminated.\n");
            return 0;
        }

        // Exec Command
        if(fork() == 0)
            execvp(cmd[0], cmd);
            
        wait(NULL);
       
    }while(1);

    free(input);
    return 0;
}