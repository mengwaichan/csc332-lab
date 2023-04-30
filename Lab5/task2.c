#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
    Nikhil Prajith Kumar
    Section: 6X
    Task 2

*/



int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Invalid arguments");
    }

    // 1st argument is the file name (quiz_grades.txt)
    // 2nd argument is the number of chapters
    // 3rd argument is the number of homeworks for each of the chapters
    // 4th is the number of students
    printf("adsasdasddas\n");
    char* filename = argv[1];
    int col = atoi(argv[2]) * atoi(argv[3]);
    int row = atoi(argv[4]);
    int grades[row][col];
    int chapters = atoi(argv[2]);
    int director = fork();
    printf("aasaS\n");
    if(director == 0){
        printf("enterance\n");
        int sourceFile = open(filename, O_RDONLY);
        printf(sourceFile);
        if(sourceFile != -1){
            printf("file opened successfully");
            char content[1];
            int number, i, j = 0;
            int check = -1;
            while(read(sourceFile, content, 1) > 0) {
                if (content[0] != ' ' && content[0] != '\n') {
                    number = number * 10;
                    number = number + atoi(content);
                    check = 1;
                } else {
                    if (check != -1) {
                        grades[i][j] = number;
                        if (j == col - 1) {
                            i++;
                            j = 0;
                        } else {
                            j++;
                        }
                    }
                    number = 0;
                    check = -1;
                }   
            }     
            grades[i][j] = number;
            /* Display the matrix */
            for (i = 0; i < row; i++)
            {
                for (j = 0; j < col; j++)
                {
                    printf("%d\t asas", grades[i][j]);
                }
                printf("\n");
            }

            // Calculate the avergae
            for(int i = 0; i < chapters; i++){
                int manager = fork();
                if(manager == 0){
                    for(int hw = 0; hw < (col / chapters); hw++){
                        printf("1");
                        int worker = fork();

                        if(worker == 0){
                            float sum = 0;
                            float average = 0;
                            for(int j = 0; j < row; j++) {
                                sum += grades[j][(i * (col / chapters)) + hw];
                            }

                            average = sum / row;

                            printf("Manager %d : Worker %d -> Average: %.2f \n", (i + 1), (hw + 1), average);
                            return 0;
                        }

                        else if(worker < 0){
                            printf("fork Failed.");
                            return 1;
                        }

                        else{
                            wait(NULL);
                        } 
                    }
                    return 0;
                }

                else if(manager < 0){
                    printf("2Erro");
                    perror("Fork failed");
                    return 1;
                } 

                else{
                    printf("3Erro");
                    wait(NULL);
                }

            }
        }

        else{
            printf("File does not exist. \n");
            return 1;
        } 


        return 0;

    }

    // Send fail statement if worker fork failed

    else if(director < 0){
        perror("Fork failed");
        return 1;
    }

    else{
        wait(NULL);
    }

    return 0;
}