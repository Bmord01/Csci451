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
#define RDWR 0666

int main(int argc, char **argv){
    /*printf("program1 %d\n",argc);
    int i;
    for(i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }*/
    FILE *inpt = fopen(argv[0],"r");
    int SIZE = 0;
    while(fgetc(inpt) != EOF){
        SIZE++;
    }
    //printf("Size = %d\n",SIZE);
    fclose(inpt);
    inpt=fopen(argv[0],"r");
    
    int writeEnd = atoi(argv[1]);
    int sid = atoi(argv[2]);
    int result;
    
    if(inpt==NULL){
        printf("ERROR Program 1\n");
    }
    char *token;
    char store[SIZE];
    memset(store,'\0',50);
    char *beforeNewLine;
    token = strtok(fgets(store,SIZE,inpt)," ");
    while(token!=NULL){
        while((result = semctl(sid,0,GETVAL,NULL))>0){
            //printf("%d\n",result);
        }
        if((beforeNewLine = strchr(token,'\n'))!=NULL){
            token[strlen(token)-1]='\0';
        }
        write(writeEnd,token,strlen(token));
        //printf("%s\n",token);
        semctl(sid,0,SETVAL,1);
        token=strtok(NULL," ");
    }
    semctl(sid,0,SETVAL,2);
    close(writeEnd);
    fclose(inpt);
    //printf("TERMINATE 1\n");
    return 0;
}
