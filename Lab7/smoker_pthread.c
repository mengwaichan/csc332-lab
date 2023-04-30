#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define CigsNumber 10

void *agentT(void* argc)
{
    int sn = *(int*)argc;
    if(sn == 1)
        printf("Put paper and match on the table, Smoker # %d\n", sn);
    else if(sn == 2)
        printf("Put match and tobacco on the table, Smoker # %d\n", sn);
    else
        printf("Put tobacco and paper on the table, Smoker # %d\n", sn);
}

void *tobaccoT(void* argc)
{
    int sn = *(int*)argc;
    printf("This is Smoker # %d, Smoker with TOBACCO picked up paper and match.\n", sn);
}

void *paperT(void* argc)
{
    int sn = *(int*)argc;
    printf("This is Smoker # %d, Smoker with PAPER picked up match and tobacco.\n", sn);
}

void *matchT(void* argc)
{
    int sn = *(int*)argc;
    printf("This is Smoker # %d, Smoker with MATCH picked up tobacco and paper.\n", sn);
}

int main()
{
    // Set random seed
    srand(time(0)); 
    // Threads
    pthread_t thread_agent, thread_paper, thread_match, thread_tobacco;

    // Create 10 times
    for(int i = 0; i < CigsNumber; ++i)
    {
        int smoker = rand()%3 + 1;
        pthread_create(&thread_agent, NULL, agentT, (void*)(&smoker));
        pthread_join(thread_agent, NULL);

        if(smoker == 1)
        {
            pthread_create(&thread_tobacco, NULL, tobaccoT, (void*)(&smoker));
            pthread_join(thread_tobacco, NULL);
        }
        else if(smoker == 2)
        {
            pthread_create(&thread_paper, NULL, paperT, (void*)(&smoker));
            pthread_join(thread_paper, NULL);
        }
        else
        {
            pthread_create(&thread_match, NULL, matchT, (void*)(&smoker));
            pthread_join(thread_match, NULL);
        }
    }
    pthread_exit(NULL);
    return 0;
}