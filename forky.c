#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int pattern1(int things);
void pattern2(int things);

int main(int __argc, char *__argv[])
{
    int things = 0;
    int pattern = 0;

    if (__argc == 3)
    {
        things = atoi(__argv[1]);
        pattern = atoi(__argv[2]);

        if(pattern == 1){
            pattern1(things);
        }
        else if(pattern == 2){
            pattern2(things);
        }

    }
}

int pattern1(int things){
    
}