#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int SIZE = 0;
char *stringOut;
int position = 0;

pthread_mutex_t lock;
pthread_cond_t threadsDone=PTHREAD_COND_INITIALIZER;
bool finished[5];

void *readOne(void * args){
    FILE *drive1 = fopen("drive1.data","r");
    char c = getc(drive1);
    bool read=false;
    int timesPos = 0;
    while(c !=EOF){
        pthread_mutex_lock(&lock);
        //printf("Read 1\n");
        stringOut[0 + (timesPos *5)] = c;
        pthread_mutex_unlock(&lock);
        timesPos++;
        c=getc(drive1);
        if(c=='\n'){
            finished[0]=true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

void *readTwo(void * args){
    FILE *drive1 = fopen("drive2.data","r");
    char c = getc(drive1);
    bool read=false;
    int timesPos = 0;
    while(c !=EOF){
        pthread_mutex_lock(&lock);
        //printf("Read 1\n");
        stringOut[1 + (timesPos *5)] = c;
        pthread_mutex_unlock(&lock);
        timesPos++;
        c=getc(drive1);
        if(c=='\n'){
            finished[1]=true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

void *readThree(void * args){
    FILE *drive1 = fopen("drive3.data","r");
    char c = getc(drive1);
    bool read=false;
    int timesPos = 0;
    while(c !=EOF){
        pthread_mutex_lock(&lock);
        //printf("Read 1\n");
        stringOut[2 + (timesPos *5)] = c;
        pthread_mutex_unlock(&lock);
        timesPos++;
        c=getc(drive1);
        if(c=='\n'){
            finished[2]=true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

void *readFour(void * args){
    FILE *drive1 = fopen("drive4.data","r");
    char c = getc(drive1);
    bool read=false;
    int timesPos = 0;
    while(c !=EOF){
        pthread_mutex_lock(&lock);
        //printf("Read 1\n");
        stringOut[3 + (timesPos *5)] = c;
        pthread_mutex_unlock(&lock);
        timesPos++;
        c=getc(drive1);
        if(c=='\n'){
            finished[3]=true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

void *readFive(void * args){
    FILE *drive1 = fopen("drive5.data","r");
    char c = getc(drive1);
    bool read=false;
    int timesPos = 0;
    while(c !=EOF){
        pthread_mutex_lock(&lock);
        //printf("Read 1\n");
        stringOut[4 + (timesPos *5)] = c;
        pthread_mutex_unlock(&lock);
        timesPos++;
        c=getc(drive1);
        if(c=='\n'){
            finished[4]=true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

void getSIZE(){
     FILE * inFile1 = fopen("drive1.data","r");
    char c= getc(inFile1);
    while((c)!=EOF && c!='\n'){
        c= getc(inFile1);
        SIZE++;
    }
    SIZE = SIZE * 5;
    fclose(inFile1);
}

void spawnThreads(pthread_t tid[]){
    pthread_create(&tid[0],NULL,readOne,NULL);
    pthread_create(&tid[1],NULL,readTwo,NULL);
    pthread_create(&tid[2],NULL,readThree,NULL);
    pthread_create(&tid[3],NULL,readFour,NULL);
    pthread_create(&tid[4],NULL,readFive,NULL);
}

void detachThreads(pthread_t tid[]){
    int i;
    for (i=0;i<5;i++){
        pthread_detach(tid[i]);
    }
}

int main(){
    int i;
    pthread_t tid[5];
    getSIZE();
    stringOut = (char *) calloc(SIZE+1,sizeof(char));
    for(i=0;i<SIZE;i++){
        stringOut[i]=' ';
    }
    stringOut[SIZE] = '\0';
    spawnThreads(tid);
    detachThreads(tid);
    for(i=0;i<5;i++){
        while(!finished[i]);
    }
    printf("%s\n",stringOut);
    free(stringOut);
    return 0;
}   
