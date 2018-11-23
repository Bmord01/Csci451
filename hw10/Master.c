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

int main(int argc, char *argv[]){
    char *inFile,*outFile;
    strcpy(inFile,argv[1]);
    strcpy(outFile,argv[2]);
    printf("%s %s\n",inFile,outFile);
    return 0;
}
