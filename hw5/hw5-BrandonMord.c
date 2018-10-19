/*  Brandon Mord
    Csci 451
    9/29/18
    Compile: gcc -g hw5-BrandonMord.c -o hw5 -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define PAGES 5000
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct pageInfo{
    int R;
    int M;
    int ProcessID;
    int using;
};

void *ThreadOne(void *args){
    int threadID=100;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pthread_mutex_lock(&lock);
        pageGrabbed=&(pageTable[pageGrab]);
        if(pageGrabbed->using==0){
            pageGrabbed->using=1;
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        pthread_mutex_unlock(&lock);
    }
}

void *ThreadTwo(void *args){
    int threadID=200;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pthread_mutex_lock(&lock);
        pageGrabbed=&(pageTable[pageGrab]);
        if(pageGrabbed->using==0){
            pageGrabbed->using=1;
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        pthread_mutex_unlock(&lock);
    }
}

void *ThreadThree(void *args){
    int threadID=300;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pthread_mutex_lock(&lock);
        pageGrabbed=&(pageTable[pageGrab]);
        if(pageGrabbed->using==0){
            pageGrabbed->using=1;
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        pthread_mutex_unlock(&lock);
    }
}

void *ThreadFour(void *args){
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    struct pageInfo *pageGrabbed;
    int i;
    while(1){
        for(i=0;i<PAGES;i++){
            pthread_mutex_lock(&lock);
            pageGrabbed=&pageTable[i];
            if(pageGrabbed->using!=0){
                if(pageGrabbed->R==1 && pageGrabbed->M!=1){
                    pageGrabbed->R=0;
                }
                else{
                    pageGrabbed->R=0;
                    pageGrabbed->M=0;
                    usleep(500);
                }
            }
            pthread_mutex_unlock(&lock);
        }
    }
}

int main(){
    struct pageInfo *pageTable = (struct pageInfo *)calloc(PAGES,sizeof(struct pageInfo));
    int i;
    pthread_t tid[4];
    srand(1492);
    
    for(i=0;i<PAGES;i++){
        pageTable[i].using=0;
        pageTable[i].R=0;
        pageTable[i].M=0;
    }
    pthread_create(&(tid[0]),NULL,ThreadOne,((void *)pageTable));
    pthread_create(&(tid[1]),NULL,ThreadTwo,((void *)pageTable));
    pthread_create(&(tid[2]),NULL,ThreadThree,((void *)pageTable));
    pthread_create(&(tid[3]),NULL,ThreadFour,((void *)pageTable));
    
    
    for(i=0;i<4;i++){
        pthread_join(tid[i],NULL);
    }
    free(pageTable);
    return 0;
}
