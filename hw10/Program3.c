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
#include <sys/shm.h>

int main(int argc, char **argv){
    /*printf("program3 %d\n",argc);
    int i;
    for(i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }*/
    
    FILE *out = fopen(argv[0],"w");
    fclose(out);
    out = fopen(argv[0],"a");
    int readEnd = atoi(argv[1]);
    int sid = atoi(argv[2]);
    int shmid = atoi(argv[3]);
    char word[50];
    memset(word,'\0',50);
    int result;
    int count =0;
    
    while((result = semctl(sid,0,GETVAL,NULL))<2){
        while((result = semctl(sid,0,GETVAL,NULL))<1){
            //printf("result = %d\n",result);
            //printf("TRAPPED HERE\n");
        }
        if((read(readEnd,&word,50) == -1)){
            break;
        }
        //printf("%s\n",word);
        if(count==0){
            fprintf(out,"%s",word);
        }
        else{
            fprintf(out," %s",word);
        }
        count++;
        memset(word,'\0',50);
        if((result = semctl(sid,0,GETVAL,NULL))<2){
            semctl(sid,0,SETVAL,0);
        }
        /*while((result=semctl(sid,0,GETVAL,NULL))!=1){
            if(result==2){
                printf("TRIED TO CONTINUE ");
                break;
            }
            printf("Stuck HERE %d \n",result);
            sleep(1);
        }*/
        
    }
    semctl(sid,0,SETVAL,3);
    while((result = semctl(sid,0,GETVAL,NULL))<4);
    int *read,*hold;
    read = (int *)shmat(shmid,0,0);
    hold=read;
    printf("Type 1: %d\n",*hold);
    *hold++;
    printf("Type 2: %d\n",*hold);
    semctl(sid,0,IPC_RMID,0);
    close(readEnd);
    fclose(out);
    //printf("TERMINATE 3\n");
    return 0;
}
