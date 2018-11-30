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
#include <semaphore.h>
#include <sys/shm.h>

int main(int argc, char **argv){
    /*printf("program2 %d\n",argc);
    int i;
    for(i=0;i<argc;i++){
        printf("%s\n",argv[i]);
    }
    */
    int readEnd = atoi(argv[0]);
    int writeEnd = atoi(argv[1]);
    int sid1 = atoi(argv[2]);
    int sid2 = atoi(argv[3]);
    int shmid = atoi(argv[4]);
    int result;
    char word[250];
    memset(word,'\0',250);
    char *empty = "";
    int type1=0,type2=0;
    char punct;
    char *s1 = "ray";
    char *s2 = "ay";
    
    while((result=semctl(sid1,0,GETVAL,NULL)!=2)){
        while((result=semctl(sid1,0,GETVAL,NULL))<1);
        while((result=semctl(sid2,0,GETVAL,NULL))!=0);
        read(readEnd,&word,250);
        //printf("%s\n",word);
        if(word[strlen(word)] ='\n'){
                word[strlen(word)-1]='\0';
            }
        if(word[0]== 'a' || word[0]== 'e' || word[0]== 'i'|| word[0]== 'o'|| word[0]== 'u' || word[0]== 'A' || word[0]== 'E' || word[0]== 'I'|| word[0]== 'O'|| word[0]== 'U')
        {
            type1++;
            if(word[strlen(word)-1]<65 || (word[strlen(word)-1]>90 && word[strlen(word)-1]<97) || word[strlen(word)-1]>122)
            {
                punct=word[strlen(word)-1];
                word[strlen(word)-1]='\0';
                strcat(word,s1);
                word[strlen(word)]=punct;
                word[strlen(word)]='\0';
            }
            else{
                strcat(word,s1);
            }
        }
        else{
            type2++;
            if(word[strlen(word)-1]<65 || (word[strlen(word)-1]>90 && word[strlen(word)-1]<97) || word[strlen(word)-1]>122)
            {
                punct=word[strlen(word)-1];
                word[strlen(word)-1]='\0';
                strcat(word,s2);
                word[strlen(word)]=punct;
                word[strlen(word)]='\0';
            }
            else{
                strcat(word,s2);
            }
        }
        //printf("%c\n",word[strlen(word)-1]);
        write(writeEnd,&word,strlen(word));
        memset(word,'\0',250);
        if((result=semctl(sid1,0,GETVAL,NULL)!=2)){
            semctl(sid1,0,SETVAL,0);
        }
        semctl(sid2,0,SETVAL,1);
    }
    semctl(sid2,0,SETVAL,2);
    while((result=semctl(sid2,0,GETVAL,NULL))<3);
    int *write,*hold;
    write = (int *)shmat(shmid,0,0);
    hold=write;
    *hold++=type1;
    *hold=type2;
    shmdt(write);
    shmdt(hold);
    semctl(sid2,0,SETVAL,4);
    semctl(sid1,0,IPC_RMID,0);
    close(readEnd);
    //printf("TERMINATE 2\n");
    return 0;
}
