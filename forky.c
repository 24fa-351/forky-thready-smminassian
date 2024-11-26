#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void pattern1(int things);
void pattern2(int things);
void child1(pid_t pid, int things, int randProcess, int sleepyTime);
void child2(int numOfChildrenToCreate);

int main(int argc, char *argv[])
{
    int things = 0;
    int pattern = 0;
    srand(time(NULL));

    if (argc == 3)
    {
        srand(time(NULL));
        things = atoi(argv[1]);
        pattern = atoi(argv[2]);
        if (pattern == 1)
        {
            pattern1(things);
        }
        else if (pattern == 2)
        {
            fprintf(stdout, "Pattern 2: creating %d processes\n", things);
            pattern2(things);
        }
    }
    return 0;
}

void pattern1(int things)
{
    int ix;
    int jx = 0;
    int wx = 0;
    int pids[things];
    fprintf(stdout, "Pattern 1: creating %d processes\n", things);

    for (int ix = 0; ix < things; ix++)
    {

        fflush(stdout);
        pid_t pid = fork();
        jx++;
        int Min = 1;
        int Max = 8;
        int sleepyTime = (rand() % (Max - Min + 1)) + Min;
        int randProcess = (rand() % things) + 1;
        if (pid == 0)
        {

            child1(pid, things, randProcess, sleepyTime);
            exit(0);
        }
        else if (pid > 0)
        {
            fprintf(stdout, "Parent created child %d with pid %d \n", jx, getpid());
            pids[ix] = pid;
        }

        else
        {
            perror("Fork Failed");
            exit(1);
        }
    }
    for (int kx = 0; kx < things; kx++)
    {
        int status;
        wx++;
        waitpid(pids[kx], &status, 0);
        fprintf(stdout, "Child %d with pid: %d completed\n", wx, pids[kx]);
        fprintf(stdout, "Parent Completed\n");
    }
}

void pattern2(int numOfChildrenToCreate)
{
    int ix;
    int jx = 1;
    fflush(stdout);
    pid_t pid = fork();

    if (pid == 0)
    {
            
        child2(numOfChildrenToCreate-1);
        exit(0);
    }
    else if(pid > 0)
    {
	    fprintf(stdout, "Parent created child with pid %d \n", getpid());
        int status;
        waitpid(pid, &status, 0);
        fprintf(stdout, "Child with pid %d exiting\n", getpid());
        fprintf(stdout, "Parent Completed\n");
    }
}

// each process is independent from each other. So this means that children should be random and process should be random

void child1(pid_t pid, int things, int randProcess, int sleepyTime)
{
    fprintf(stdout, "child Process %d (pid %d) created: will sleep for %d seconds\n", randProcess, getpid(), sleepyTime);
    sleep(sleepyTime);
    fprintf(stdout, "child Process %d (pid %d): exiting\n", randProcess, getpid());
    
}

void child2(int numOfChildrenToCreate)
{
      int Min = 1;
      int Max = 8;
      int sleepyTime = (rand() % (Max - Min + 1)) + Min;
        if(numOfChildrenToCreate == 0){
            sleep(sleepyTime);
            return;
        }
            pid_t grandChild_pid = fork();
           
            if (grandChild_pid == 0)
            {
                
                fprintf(stdout, "Grandchild with pid %d created \n", getpid());
                child2(numOfChildrenToCreate-1);
                exit(0);
            }
            else if (grandChild_pid > 0)
            {
            	int status;
                waitpid(grandChild_pid, &status, 0);
                fprintf(stdout, "grandchild with pid: %d exiting\n", grandChild_pid);
            }
      
    }