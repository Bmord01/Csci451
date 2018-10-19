/*
    Brandon Mord
    CSCI 451
    Homework 6
    10/5/18
    Program 1
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
    if(result != 0){
        return -1;
    }
    else{
        semctl(sid, 0, SETVAL, 1);
        printf("Executing Program #1\n");
    }
    return 0;
}
