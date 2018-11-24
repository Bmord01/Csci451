/*Brandon Mord
Homework 10
Csci 451
Edits:
    11/23/18
    
*/
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
#include <sys/wait.h>

int main(int argc, char **argv){
    //////////////////////////////////////////
    /*      Get Input from command line     */
    char *inFile,*outFile;
    inFile=argv[1];
    outFile=argv[2];
    //////////////////////////////////////////
    
    //////////////////////////////////////////
    /*      Create Pipes                    */
    /*      pipe[0] = read  pipe[1] = write */
    int pipe1[2],pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    //////////////////////////////////////////
    
    //////////////////////////////////////////
    /*      Create Both Semaphores          */
    key_t SKey1 = ftok("input.txt",1);
    key_t SKey2 = ftok("output.txt",1);
    int sid1,sid2;
    sid1=semget(SKey1,1,0660 | IPC_CREAT);
    semctl(sid1,0,SETVAL,0);
    sid2=semget(SKey2,1,0660 | IPC_CREAT);
    semctl(sid2,0,SETVAL,0);
    //printf("%d %d ",sid1,sid2);
    //////////////////////////////////////////
    
    //////////////////////////////////////////
    /*      Create Shared Memory Segment    */
    key_t SKey3 = ftok("Master.c",3);
    int shmid = shmget(SKey3,2048,0660 | IPC_CREAT);
    //printf("%d\n",shmid);
    //////////////////////////////////////////
    
    //////////////////////////////////////////
    pid_t pid1,pid2,pid3;
    char *p1 = "p1", *p2 = "p2", *p3 = "p3";
    char readEnd1[100],writeEnd1[100],readEnd2[100],writeEnd2[100];
    char Sem1C[100],Sem2C[100],SharedMem[100];
    sprintf(Sem1C,"%d",sid1);
    sprintf(Sem2C,"%d",sid2);
    sprintf(readEnd1,"%d",pipe1[0]);
    sprintf(writeEnd1,"%d",pipe1[1]);
    sprintf(readEnd2,"%d",pipe2[0]);
    sprintf(writeEnd2,"%d",pipe2[1]);
    sprintf(SharedMem,"%d",shmid);
    
    char *const parmList1[] = {inFile,writeEnd1,Sem1C,NULL};
    pid1=fork();
    if(pid1==0){
        execv(p1,parmList1);
    }
    pid2=fork();
    char *const parmList2[] = {readEnd1,writeEnd2,Sem1C,Sem2C,SharedMem,NULL};
    if(pid2==0){
        execv(p2,parmList2);
    }
    char *const parmList3[] = {outFile,readEnd2,Sem2C,SharedMem,NULL};
    pid3=fork();
    if(pid3==0){
        execv(p3,parmList3);
    }
    
    int status;
    waitpid(pid1,&status,0);
    waitpid(pid2,&status,0);
    waitpid(pid3,&status,0);
    semctl(sid1,0,IPC_RMID,0);
    semctl(sid2,0,IPC_RMID,0);
    //printf("TERMINATE MASTER\n");
    return 0;
}
