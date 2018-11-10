/************************************************/
/* Produces a character once every 120 seconds. */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main(void) {
int i;
char number;
FILE *output;
    key_t SKey = ftok("program3.c",1);
    int sid = semget(SKey,1,0660 | IPC_CREAT);
    semctl(sid,0,SETVAL,0);
    while (1) {
       for (i = 58; i < 127; i++) {
           semctl(sid,0,SETVAL,1);
           output = fopen("./output3.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           semctl(sid,0,SETVAL,0);
           sleep(120);
       }
    }
    return 1;
}
