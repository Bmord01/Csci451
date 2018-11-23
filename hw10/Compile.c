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

int main(){
    system("gcc -g Master.c -o m -lpthread");
    system("gcc -g Program1.c -o p1");
    system("gcc -g Program2.c -o p2");
    system("gcc -g Program3.c -o p3");
    return 0;
}
