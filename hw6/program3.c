/*
    Brandon Mord
    CSCI 451
    Homework 6
    10/5/18
    Program 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

int main(){
    key_t SKey = ftok("program0.c", 1);
    int sid;
    sid = semget(SKey, 1, 0660 | IPC_CREAT);
    int result = semctl(sid,0,GETVAL,NULL);
    if(result != 2){
        return -1;
    }
    else{
        semctl(sid, 0, IPC_RMID);
        printf("Executing Program #3\n");
    }
    return 0;
}
