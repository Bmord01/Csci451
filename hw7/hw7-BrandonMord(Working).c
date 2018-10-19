#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int SIZE = 0;
char *stringOut;
int position = 0;

pthread_mutex_t lock,lock2;
pthread_cond_t read1=PTHREAD_COND_INITIALIZER,read2=PTHREAD_COND_INITIALIZER,
    read3=PTHREAD_COND_INITIALIZER,read4=PTHREAD_COND_INITIALIZER,read5=PTHREAD_COND_INITIALIZER;
bool finished = false;

void *readOne(void * args){
    FILE *drive1 = fopen("drive1.data","r");
    char c = getc(drive1);
    bool read=false;
    while(c !=EOF){
        while (!read){
            pthread_mutex_lock(&lock);
            if((position % 5)==0){
                //printf("Read 1\n");
                stringOut[position] = c;
                position++;
                read=true;
            }
            pthread_mutex_unlock(&lock);
        }
        read=false;
        c=getc(drive1);
        if(c=='\n'){
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
    while(c !=EOF){
        while (!read){
            pthread_mutex_lock(&lock);
            if((position % 5)==1){
                //printf("Read 2\n");
                stringOut[position] = c;
                position++;
                read=true;
            }
            pthread_mutex_unlock(&lock);
        }
        read=false;
        c=getc(drive1);
        if(c=='\n'){
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
    while(c !=EOF){
        while (!read){
            pthread_mutex_lock(&lock);
            if((position % 5)==2){
                //printf("Read 3\n");
                stringOut[position] = c;
                position++;
                read=true;
            }
            pthread_mutex_unlock(&lock);
        }
        read=false;
        c=getc(drive1);
        if(c=='\n'){
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
    while(c !=EOF){
        while (!read){
            pthread_mutex_lock(&lock);
            if((position % 5)==3){
                //printf("Read 4\n");
                stringOut[position] = c;
                position++;
                read=true;
            }
            pthread_mutex_unlock(&lock);
        }
        read=false;
        c=getc(drive1);
        if(c=='\n'){
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
    while(c !=EOF){
        while (!read){
            pthread_mutex_lock(&lock);
            if((position % 5)==4){
                //printf("Read 5\n");
                stringOut[position] = c;
                position++;
                read=true;
            }
            pthread_mutex_unlock(&lock);
        }
        read=false;
        c=getc(drive1);
        if(c=='\n'){
            finished = true;
            return NULL;
        }
    }
    fclose(drive1);
    return NULL;
}

int main(){
    FILE * inFile1 = fopen("drive1.data","r");
    char c= getc(inFile1);
    while((c)!=EOF && c!='\n'){
        c= getc(inFile1);
        SIZE++;
    }
    SIZE = SIZE * 5;
    fclose(inFile1);
    //printf("%d\n",SIZE);
    stringOut = (char *) calloc(SIZE+1,sizeof(char));
    stringOut[SIZE] = '\0';
    pthread_t tid[5];
    pthread_create(&tid[0],NULL,readOne,NULL);
    pthread_create(&tid[1],NULL,readTwo,NULL);
    pthread_create(&tid[2],NULL,readThree,NULL);
    pthread_create(&tid[3],NULL,readFour,NULL);
    pthread_create(&tid[4],NULL,readFive,NULL);
    int i;
    for (i=0;i<5;i++){
        pthread_detach(tid[i]);
    }
    while(!finished);
    printf("%s\n",stringOut);
    free(stringOut);
    return 0;
}   
