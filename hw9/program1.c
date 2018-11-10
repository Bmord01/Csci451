/************************************************/
/* Produces an even value once every second.    */
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
    key_t SKey = ftok("program1.c",1);
    int sid = semget(SKey,1,0660 | IPC_CREAT);
    semctl(sid,0,SETVAL,0);
    while (1) {
       for (i = 0; i < 10; i+=2) {
           semctl(sid,0,SETVAL,1);
           output = fopen("./output1.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           semctl(sid,0,SETVAL,0);
           sleep(1);
       }
    }
    return 1;
}
