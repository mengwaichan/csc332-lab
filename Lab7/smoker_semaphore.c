#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sem.h"

#define CigsNumber 10

static int smoker;
static int STOP = 0;

int main()
{
	srand(time(0));
	int pid;

	// Create semaphores for each of the processes
	int lock = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
	int agent = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
	int smokerTobacco = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
	int smokerPaper = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);
	int smokerMatch = semget(IPC_PRIVATE, 1,0666 | IPC_CREAT);

	// Initialize the semaphores
	sem_create(lock, 1);
	sem_create(agent, 0);
	sem_create(smokerTobacco, 0);
	sem_create(smokerPaper, 0);
	sem_create(smokerMatch, 0);

	if ((pid = fork()) == 0)
	{
		while(!STOP)
		{
			P(smokerTobacco);
			P(lock);
			printf("Smoker #1 with tobacco has picked up paper and match!\n");
			V(agent);
			V(lock);
		}
	}
	else
	{
		// Agent process
		if((pid = fork()) == 0)
		{
			while(!STOP)
			{
				P(smokerPaper);
				P(lock);
				printf("Smoker #2 with paper has picked up match and tobacco!\n");
				V(agent);
				V(lock);
			}
		}
		else
		{
			// Agent process
			if((pid = fork()) == 0)
			{
				while(!STOP)
				{
					P(smokerMatch);
					P(lock);
					printf("Smoker #3 with match has picked up tobacco and paper!\n");
					V(agent);
					V(lock);
				}
			}
			else
			{
				// Agent process
				for(int i = 0; i < CigsNumber; ++i)
				{
					P(lock);
					smoker = rand()%3 + 1;
					if(smoker == 1)
					{
						// paper and match
						printf("Put paper and match on the table, Smoker # %d\n", smoker);
						V(smokerTobacco);
					}
					else if(smoker == 2)
					{
						// match and tobacco
						printf("Put match and tobacco on the table, Smoker # %d\n", smoker);
						V(smokerPaper);
					}
					else
					{
						// tobacco and paper
						printf("Put tobacco and paper on the table, Smoker # %d\n", smoker);
						V(smokerMatch);
					}
					if(i == CigsNumber - 1)
						STOP = 1;
					V(lock);
					P(agent);
				}
			}
		}
	}

	return 0;
}