#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int i;
    int totalLen = 0;
    for(i=1;i<argc;i++){
        totalLen += ((int) strlen(argv[i]));
        if(i!=(argc-1)){
            totalLen +=1;
        }
    }
    char cmd[totalLen];
    for(i=1;i<argc;i++){
        strcat(cmd,argv[i]);
        strcat(cmd," ");
    }
    strcat(cmd,">> output.txt");
    system(cmd);
    return 0;
}
