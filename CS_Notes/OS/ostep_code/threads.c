#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"

int loops;
volatile int counter = 0;

void *worker(void *arg)
{
    for(int i = 0; i < loops; i++)
    {
        counter++;
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: threads <integer>\n");
        exit(1);
    }
    
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value: %d\n", counter);

    pthread_create(&p1, NULL, worker, NULL);
    pthread_create(&p2, NULL, worker, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("final value: %d\n", counter);

    return 0;
}
