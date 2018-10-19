/*
    Brandon Mord
    CSCI 451
    Homework 6
    10/5/18
    Program 0
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>

int main(void){
    key_t SKey = ftok("program0.c", 1);
    int sid;
    sid = semget(SKey, 1, 0660 | IPC_CREAT);
    if (semctl(sid, 0, SETVAL, 0) == -1) {
        perror("semctl");
        return -1;
    }
    printf("Executing Program #0\n");
    return 0;
} 
