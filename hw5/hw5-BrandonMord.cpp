#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define PAGES 5000

struct pageInfo{
    int R;
    int M;
    int ProcessID;
    pthread_mutex_t lock;
} page;

void *ThreadOne(void *args){
    int threadID=100;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    int i=0;
    srand(1492);
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pageGrabbed=&(pageTable[pageGrab]);
        if((pthread_mutex_trylock(&(pageGrabbed->lock)))==0){
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
            pthread_mutex_unlock(&(pageGrabbed->lock));
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        i++;
    }
}

void *ThreadTwo(void *args){
    int threadID=200;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    int i=0;
    srand(1492);
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pageGrabbed=&pageTable[pageGrab];
        if((pthread_mutex_trylock(&(pageGrabbed->lock)))==0){
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
            pthread_mutex_unlock(&(pageGrabbed->lock));
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        i++;
    }
}

void *ThreadThree(void *args){
    int threadID=300;
    int pageGrab,task;
    struct pageInfo *pageGrabbed;
    int i=0;
    srand(1492);
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    while(1){
        pageGrab=(rand()%5000);
        task=rand()%2;
        pageGrabbed=&pageTable[pageGrab];
        if((pthread_mutex_trylock(&(pageGrabbed->lock)))==0){
            pageGrabbed->ProcessID=threadID;
            if(task==0){
                pageGrabbed->R=1;
            }
            else{
                pageGrabbed->R=1;
                pageGrabbed->M=1;
            }
            pthread_mutex_unlock(&(pageGrabbed->lock));
        }
        else{
            printf("Page fault: %d\n",pageGrab);
        }
        i++;
    }
}

void *ThreadFour(void *args){
    struct pageInfo *pageTable = ((struct pageInfo *) args);
    int i;
    int class1=-1,class2=-2,class3=-3;
    while(1){
        break;
    }
}

int main(){
    struct pageInfo *pageTable = (struct pageInfo *)calloc(PAGES,sizeof(struct pageInfo));
    int i;
    pthread_t tid[4];
    tid[0]=100;
    tid[1]=200;
    tid[2]=300;
    srand(1492);
    struct pageInfo *pageTest = &pageTable[3257];
    
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
