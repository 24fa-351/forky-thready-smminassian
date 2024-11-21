#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


void pattern1(int things, FILE *fptr);
// void pattern2(int things);
void childPattern1(pid_t pid, FILE *fptr, int things);

int main(int argc, char *argv[])
{
    int things = 0;
    int pattern = 0;

    FILE *fptr;
    fptr = fopen("results.txt", "w");

    if (argc == 3)
    {
    	srand(time(NULL));
        things = atoi(argv[1]);
        pattern = atoi(argv[2]);
        if (pattern == 1)
        {
            pattern1(things, fptr);
        }
        // else if (pattern == 2)
        // {
        //     pattern2(things);
        // }
    }
}

void pattern1(int things, FILE *fptr)
{
    int ix;
    int pids[things];
    fprintf(fptr, "Pattern 1: creating %d processes\n", things);
    
    for(int ix = 1; ix < things ; ix++){
    
    	fflush(fptr);
      	pid_t pid = fork();
    	
    	if(pid == 0){
    		fprintf(fptr, "Parent created child %d with pid %d \n", ix, getpid());
        	childPattern1(pid, fptr, things);
        	exit(0);
        }
        else if(pid > 0){
    		int status;
    		waitpid(pids[ix], &status, 0);
		fprintf(fptr, "Child %d with pid: %d completed\n", ix, getpid());
		}
     		
        else{
     		perror("Fork Failed");
     		exit(1);
     	}  
     	} 
     } 



// each process is independent from each other. So this means that children should be random and process should be random

void childPattern1(pid_t pid, FILE *fptr, int things)
{
    int Min = 1;
    int Max = 8;
    int sleepyTime = (rand() % (Max-Min + Min) + Min);
    int randProcess = (rand() % (things - Min + Min) + Min);
    
    fprintf(fptr, "Process %d (pid %d) created: will sleep for %d seconds\n", randProcess, getpid(), sleepyTime);
    sleep(sleepyTime);
    fprintf(fptr, "Process %d (pid %d): exiting\n", randProcess, getpid());
}