#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

const char *FILENAME = "quiz_grades.txt";

void worker(int student, int chapter, int homework, int ch, int hw, int grades[student][chapter*homework]){
    double sum = 0.0;
    for(int s = 0; s < student; s++)
        sum += grades[s][ch * homework + hw];
    double avg = sum / student;
    printf("Average grade for chapter %d in homework %d is %.2f.\n",ch+1, hw+1, avg);
    exit(0);   
}

void manager(int student, int chapter, int homework, int ch,int grades[student][chapter * homework]){
    for(int hw = 0; hw < homework; hw++)
            {
                int worker_fork = fork();
                if(worker_fork == 0)
                    worker(student, chapter, homework, ch, hw, grades);
            
                wait(NULL);    
            }

    exit(0);
}

void get_grades(int student, int chapter, int homework, int grades[student][chapter * homework]){
    FILE *fp = fopen(FILENAME, "r");
    size_t size = 100;
    char *row = malloc(size * sizeof(char));
    char *buf;

    for(int i = 0; i < student; i++){
        int row_iter = 0;
        getline(&row, &size, fp);
        for(int j = 0; j < chapter*homework; j++){
            while (!isdigit(row[row_iter]))
                row_iter++;
            buf = &row[row_iter];
            while (isdigit(row[row_iter]))
                row_iter++;
            row[row_iter] = '\0';
            row_iter++;
            grades[i][j] = atoi(buf);
        }
    }
    free(row);
    fclose(fp);
}

int main(int argc, char* argv[]){
    int student, chapter, homework;

    printf("Please Enter Number of Students  : ");  
    scanf("%d", &student);

    printf("Please Enter Number of Chapters  : ");  
    scanf("%d", &chapter);

    printf("Please Enter Number of Homeworks : ");  
    scanf("%d", &homework);

    int grades[student][chapter * homework];
    get_grades(student, chapter, homework, grades);

    for(int i = 0; i < chapter; i++){
        int manager_fork = fork();
        if(manager_fork == 0)
            manager(student, chapter, homework, i, grades);
        wait(NULL);
    }

    return 0;
}