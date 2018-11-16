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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

bool next1=false,next2=false,next3=false;

void *readData1(void *args){
    FILE *inpt,*outpt;
    int inSID = (int)args;
    key_t SKey = ftok("program1.c",1);
    int sid;
    int prev1=0,count=0,current=0,result=-1;
    bool print=false;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output1.txt","r");
                while(inpt==NULL){
                    inpt=fopen("output1.txt","r");
                }
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    print=true;
                }
                if(print){
                    //while((result = semctl(inSID,0,GETVAL,NULL))!=0);
                    if((result = semctl(inSID,0,GETVAL,NULL))==0){
                        outpt=fopen("output4.txt","a");
                        fprintf(outpt,"Thread 1: %d\n",current);
                        printf("Thread 1: %d\n",current);
                        fclose(outpt);
                        prev1=current;
                        print=false;
                        semctl(inSID,0,SETVAL,1);
                    }
                }
                else{
                    semctl(inSID,0,SETVAL,0);
                }
            }
        }
        usleep(500000);
    }
    return NULL;
}

void *readData2(void *args){
    FILE *inpt,*outpt;
    int inSID = (int)args;
    key_t SKey = ftok("program2.c",1);
    int sid;
    int prev1=0,count=0,current=0,result=-1;
    bool print =false;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output2.txt","r");
                while(inpt==NULL){
                    inpt=fopen("output1.txt","r");
                }
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    print=true;
                }
                if(print){
                    //while((result = semctl(inSID,0,GETVAL,NULL))!=1);
                    if((result = semctl(inSID,0,GETVAL,NULL))==1){
                        outpt=fopen("output4.txt","a");
                        fprintf(outpt,"Thread 2: %d\n",current);
                        printf("Thread 2: %d\n",current);
                        fclose(outpt);
                        prev1=current;
                        print=false;
                        semctl(inSID,0,SETVAL,2);
                    }
                    
                }
                else{
                    semctl(inSID,0,SETVAL,0);
                }
            }
        }
        usleep(500000);
    }
    return NULL;
}

void *readData3(void *args){
    FILE *inpt,*outpt;
    int inSID = (int)args;
    key_t SKey = ftok("program3.c",1);
    int sid;
    int prev1=0,count=0,current=0,result=-1;
    bool print=false;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output3.txt","r");
                while(inpt==NULL){
                    inpt=fopen("output1.txt","r");
                }
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    print=true;
                }
                if(print){
                    //while((result = semctl(inSID,0,GETVAL,NULL))!=2);
                    if((result = semctl(inSID,0,GETVAL,NULL))==2){
                        outpt=fopen("output4.txt","a");
                        fprintf(outpt,"Thread 3: %c\n",current);
                        printf("Thread 3: %c\n",current);
                        fclose(outpt);
                        prev1=current;
                        print=false;
                        semctl(inSID,0,SETVAL,0);
                    }
                }
                else{
                    semctl(inSID,0,SETVAL,0);
                }
            }
        }
        usleep(500000);
    }
    return NULL;
}

int main(){
    pthread_t tids[3];
    int i;
    key_t SKey = ftok("program4.c",1);
    int sid = semget(SKey,1,0660 | IPC_CREAT);
    printf("SID = %d\n",sid);
    semctl(sid,0,SETVAL,0);
    usleep(1);
    pthread_create(&tids[0],NULL,readData1,((void *) sid));
    pthread_create(&tids[1],NULL,readData2,((void *) sid));
    pthread_create(&tids[2],NULL,readData3,((void *) sid));
    for(i=0;i<3;i++){
        pthread_detach(tids[i]);
    }
    while(1);
    return 0;
}
