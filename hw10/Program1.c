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
    int inpt;
    inpt=open(argv[0],O_RDONLY);
    
    int writeEnd = atoi(argv[1]);
    int sid = atoi(argv[2]);
    int result;
    
    char holder[250];
    memset(holder,'\0',250);
    char final[250];
    memset(final,'\0',250);
    char in;
    int pos=0;
    
   while((read(inpt,&in,1))!=0){
        while((result = semctl(sid,0,GETVAL,NULL))>0){
            //printf("%d\n",result);
        }
        if(in!=' '){
            //printf("%c\n",in);
            holder[pos]=in;
            pos++;
        }
        else{
            strcpy(final,holder);
            //printf("%s\n",final);
            write(writeEnd,final,strlen(final));
            semctl(sid,0,SETVAL,1);
            pos=0;
            memset(holder,'\0',250);
        }
    }
    while((result = semctl(sid,0,GETVAL,NULL))>0){
            //printf("%d\n",result);
    }
    strcpy(final,holder);
    //printf("%s\n",final);
    final[strlen(final)-1] = '\0';
    write(writeEnd,final,strlen(final));
    semctl(sid,0,SETVAL,1);
    pos=0;
    memset(holder,'\0',250);
    semctl(sid,0,SETVAL,2);
    close(writeEnd);
    close(inpt);
    //printf("TERMINATE 1\n");
    return 0;
}
