#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdbool.h>

int main(){
    int files[4];
    files[0] = open("shared1.dat",0666);
    files[1] = open("shared2.dat",0666);
    files[2] = open("temp2.data", 0666);
    files[3] = creat("temp3.data",0666);
    
    char inS1,inS2;
    read(files[0],&inS1,1);
    read(files[1],&inS2,1);
    //printf("%c %c\n",inS1,inS2);
    
    char in;
    char blank = ' ';
    while(read(files[2],&in,1) != 0){
        if(in == '\n'){
            write(files[3],&blank,1);
        }
        else{
            write(files[3],&in,1);
        }
    }
    int i;
    
    for(i=0;i<4;i++){
        close(files[i]);   
    }
    return 0;
}
