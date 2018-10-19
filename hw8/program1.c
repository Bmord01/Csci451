#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

#define READ 0444
#define RDWR 0666

int main(){
    int fdR,fdW;
    char in;
    char newLine = '\n';
    fdR=open("input.data",O_RDONLY);
    fdW=creat("temp1.data",RDWR);
    
    while(read(fdR,&in,1)!=0){
        if(in == ' '){
            write(fdW,&newLine,1);
        }
        else{
            write(fdW,&in,1);
        }
    }
    close(fdR);
    close(fdW);
    return 0;
}
