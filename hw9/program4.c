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

pthread_mutex_t lock;

void *readData1(void *args){
    FILE *inpt,*outpt;
    int inSID = (int)args;
    key_t SKey = ftok("program1.c",1);
    int sid;
    int prev1=0,prev2=0,current=0,result=-1;;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output1.txt","r");
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    if((result = semctl(inSID,0,GETVAL,NULL)==0)){
                        if(prev1==prev2){
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d%d",prev1,prev2);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,1);
                        }
                        else{
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d",prev1);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,1);
                            //write prev1 to output4.txt
                        }
                    }
                    prev1=current;
                }
                else if(prev1!=prev2){
                    prev2=prev1;
                }
                else{
                    if((result=semctl(inSID,0,GETVAL,NULL))==0){
                        semctl(inSID,0,SETVAL,1);
                    }
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
    int prev1=0,prev2=0,current=0,result=-1;;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output2.txt","r");
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    if((result = semctl(inSID,0,GETVAL,NULL)==1)){
                        if(prev1==prev2){
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d%d",prev1,prev2);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,0);
                        }
                        else{
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d",prev1);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,0);
                            //write prev1 to output4.txt
                        }
                    }
                    prev1=current;
                }
                else if(prev1!=prev2){
                    prev2=prev1;
                }
                else{
                    if((result=semctl(inSID,0,GETVAL,NULL))==0){
                        semctl(inSID,0,SETVAL,0);
                    }
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
    int prev1=0,prev2=0,current=0,result=-1;;
    while(1){
        if((sid=semget(SKey,1,0660))>-1){
            if((result=semctl(sid,0,GETVAL,NULL))!=1){
                //printf("Inside of reading\n");
                inpt=fopen("output3.txt","r");
                fscanf(inpt,"%d",&current);
                fclose(inpt);
                if(current!=prev1){
                    if((result = semctl(inSID,0,GETVAL,NULL)==2)){
                        if(prev1==prev2){
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d%d",prev1,prev2);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,0);
                        }
                        else{
                            outpt = fopen("output4.txt","a");
                            fprintf(outpt,"%d",prev1);
                            fclose(outpt);
                            semctl(inSID,0,SETVAL,0);
                            //write prev1 to output4.txt
                        }
                    }
                    prev1=current;
                }
                else if(prev1!=prev2){
                    prev2=prev1;
                }
                else{
                    if((result=semctl(sid,0,GETVAL,NULL))==2){
                        semctl(inSID,0,SETVAL,0);
                    }
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
    pthread_create(&tids[0],NULL,readData1,((void *) sid));
    pthread_create(&tids[1],NULL,readData2,((void *) sid));
    //pthread_create(&tids[2],NULL,readData3,((void *) sid));
    for(i=0;i<2;i++){
        pthread_detach(tids[i]);
    }
    while(1);
    return 0;
}
