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
        inpt=fopen("output2.txt","r");
        fscanf(inpt,"%d",&current);
        fclose(inpt);
        if(current!=prev1){
            prev1=current;
            printf("P1 %d\n",current);
        }
        else if(prev1!=prev2){
            prev2=prev1;
            printf("P1 %d\n",current);
        }
        usleep(500000);
    }
    return NULL;
}

void *readData2(void *args){
    FILE *inpt;
    int prev1=0,prev2=0,current=0;
    while(1){
        inpt=fopen("output1.txt","r");
        fscanf(inpt,"%d",&current);
        fclose(inpt);
        if(current!=prev1){
            prev1=current;
            printf("P2 %d\n",current);
        }
        else if(prev1!=prev2){
            prev2=prev1;
            printf("P2 %d\n",current);
        }
        usleep(500000);
    }
    return NULL;
}

void *readData3(void *args){
    FILE *inpt;
    int prev1=0,prev2=0,current=0;
    while(1){
        inpt=fopen("output3.txt","r");
        fscanf(inpt,"%d",&current);
        fclose(inpt);
        if(current!=prev1){
            prev1=current;
            printf("P3 %d\n",current);
        }
        else if(prev1!=prev2){
            prev2=prev1;
            printf("P3 %d\n",current);
        }
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
