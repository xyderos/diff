#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAXSIZE 25
#define MAXWORKERS 3

char *b1, *b2, *l1, *l2;

FILE *file1;

FILE *file2;

int done1 = 0;

int done2 = 0;

int done = 0;

void *Producer1(void *arg){

    while(!done){

        if (!done1){
            l1 = fgets(b1, MAXSIZE, file1);
            done1 = 1;
        }
    }
    return NULL;
}
void *Producer2(void *arg){

    while(!done){

        if(!done2){
            l2 = fgets(b2, MAXSIZE, file2);
            done2 = 1;
        }
    }
    return NULL;
}
void *Consumer(void *arg){

    while(!done){
        while(!(done1 && done2)){}

        if(l1 == NULL && l2 == NULL) done = 1;

        else if(l1 == NULL){
            printf("> %s", l2);
            done2 = 0;
        }
        else if(l2 == NULL){
            printf("> %s", l1);
            done1 = 0;
        }
        else{
            if(strcmp(l1, l2) == 0){
                done1 = 0;
                done2 = 0;
            }else{
                printf("< %s---\n> %s", l1, l2);
                done1 = 0;
                done2 = 0;
            }

        }
    }
    return NULL;
}

int main(int argc, char *argv[]){

    file1 = fopen(argv[1], "r");

    file2 = fopen(argv[2], "r");

    b1 = malloc(sizeof(char) * MAXSIZE);

    b2 = malloc(sizeof(char) * MAXSIZE);

    pthread_attr_t attr;

    pthread_t workerid[MAXWORKERS];

    pthread_attr_init(&attr);

    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    pthread_create(&workerid[1], &attr, Producer1, (void *) 1);

    pthread_create(&workerid[2], &attr, Producer2, (void *) 2);

    pthread_create(&workerid[3], &attr, Consumer, (void *) 3);

    pthread_exit(NULL);
}