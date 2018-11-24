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

int main(int argc, char **argv){
    /*printf("program3 %d\n",argc);
    int i;
    for(i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    
    FILE *out = fopen(argv[0],"w");
    int readEnd = atoi(argv[1]);
    int sid = atoi(argv[2]);
    int shmid = atoi(argv[3]);
    char word[50];
    memset(word,'\0',50);
    int result;
    
    while((result = semctl(sid,0,GETVAL,NULL)!=2)){ 
        read(readEnd,&word,50);
        printf("%s\n",word);
        memset(word,'\0',50);
        if((result = semctl(sid,0,GETVAL,NULL))!=2){
            semctl(sid,0,SETVAL,0);
        }
        while((result=semctl(sid,0,GETVAL,NULL))!=1){
            if(result==2){
                printf("TRIED TO CONTINUE ");
                break;
            }
            printf("Stuck HERE %d \n",result);
            sleep(1);
        }
    }
    fclose(out);*/
    return 0;
}
