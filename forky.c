#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void pattern1(int things, FILE *fptr);
// void pattern2(int things);
void childPattern1(int children, pid_t pid, FILE *fptr, int things);

int main(int __argc, char *__argv[])
{
    int things = 0;
    int pattern = 0;

    FILE *fptr;
    fptr = fopen("results.txt", "w");

    if (__argc == 3)
    {
        things = atoi(__argv[1]);
        pattern = atoi(__argv[2]);

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
    // int duplicateProcess[things];
    

    // int dupProcessCount = 0;

    for (ix = 1; ix <= things; ix++)
    {
        int children = rand() % (5);
        // if(dupProcessCount != 0){
        //     if(duplicateProcess[dupProcessCount] = randProcess){

        //     }
        fprintf(fptr, "Pattern 1: creating %d processes\n", things);
        pid_t pid = fork();
        for (int dx = 0; dx <= children; dx++)
        {
            fprintf(fptr, "Parent created child %d (pid %d)\n", dx, getpid());
        }
        childPattern1(children, pid, fptr, things);
    }
}

// each process is independent from each other. So this means that children should be random and process should be random

void childPattern1(int children, pid_t pid, FILE *fptr, int things)
{
    int Min = 1;
    int Max = 8;
    int sleepyTime = (rand() % (Max-Min + Min) + Min);
    int randProcess = (rand() % (things - Min + Min) + Min);

    fprintf(fptr, "Process %d (pid %d) created: will sleep for %d seconds\n", randProcess, getpid(), sleepyTime);
    sleep(sleepyTime);
    fprintf(fptr, "Process %d (pid %d): exiting\n", randProcess, getpid());
}