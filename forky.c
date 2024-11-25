#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

void pattern1(int things);
void pattern2(int things);
void child(pid_t pid, int things, int randProcess, int sleepyTime, bool isGrandChild);

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
        // int makeMoreProcesses = (rand() % 1) + 1;
        if (pid == 0)
        {

            child(pid, things, randProcess, sleepyTime, false);
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
    }
}

void pattern2(int numOfChildrenToCreate)
{
    int ix;
    int jx = 1;
    int Min = 1;
    int Max = 8;
    int sleepyTime = (rand() % (Max - Min + 1)) + Min;
    int randProcess = (rand() % things) + 1;
    

    fflush(stdout);
    pid_t pid = fork();

    
    if (pid == 0){
            child(numOfChildrenToCreate-1);
            exit(0);
       
           
        

        else
        {
            perror("Fork Failed");
            exit(1);
        }
        fprintf(stdout, "Grandchild with pid %d exiting\n", getpid());
        exit(0);
    

}
else if(pid > 0)
    {
        fprintf(stdout, "Pattern 2: creating %d processes\n", things);
	    fprintf(stdout, "Parent created child with pid %d \n", getpid());
        int status;
        waitpid(pid, &status, 0);
        fprintf(stdout, "Child with pid %d exiting\n", getpid());
        fprintf(stdout, "Parent Completed\n");
    }
}

// each process is independent from each other. So this means that children should be random and process should be random

void child(int numOfChildrenToCreate)
{
      int sleepyTime = (rand() % (Max - Min + 1)) + Min;
        if(numOfChildrenToCreate == 0){
            //sleep
            return;
        }
            pid_t grandChild_pid = fork();
           
            if (grandChild_pid == 0)
            {
                
                fprintf(stdout, "Grandchild with pid %d created grandchild with pid %d \n", getpid(), getpid());
                child(numOfChildrenToCreate-1);
                exit(0);
            }
            else if (grandChild_pid > 0)
            {
                fprintf(stdout, "Child created GrandChild with pid %d \n", grandChild_pid);
            	int status;
                waitpid(pid, &status, 0);
                fprintf(stdout, "grandchild with pid: %d exiting\n", grandChild_pid);
            }
      
    }
// need to have this as a different function for pattern 2
