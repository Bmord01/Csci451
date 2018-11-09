#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>
#include <pthread.h>


pthread_mutex_t lock;

void *readData1(void *args){
    FILE *inpt;
    int prev1=0,prev2=0,current=0;
    while(1){
        
        usleep(500000);
    }
    return NULL;
}

void *readData2(void *args){
    FILE *inpt;
    int prev1=0,prev2=0,current=0;
    while(1){
        
        usleep(500000);
    }
    return NULL;
}

void *readData3(void *args){
    FILE *inpt;
    int prev1=0,prev2=0,current=0;
    while(1){
        
        usleep(500000);
    }
    return NULL;
}

int main(){
    pthread_t tids[3];
    pthread_create(&tids[0],NULL,readData1,NULL);
    pthread_detach(tids[0]);
    pthread_create(&tids[1],NULL,readData2,NULL);
    pthread_detach(tids[1]);
    pthread_create(&tids[2],NULL,readData3,NULL);
    pthread_detach(tids[2]);
    return 0;
}
