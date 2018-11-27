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
    char holder[50];
    memset(holder,'\0',50);
    char final[50];
    memset(final,'\0',50);
    char in;
    int fd;
    fd = open("input.txt",O_RDONLY);
    int pos=0;
    while((read(fd,&in,1))!=0){
        if(in!=' '){
            //printf("%c\n",in);
            holder[pos]=in;
            pos++;
        }
        else{
            strcpy(final,holder);
            printf("%s\n",final);
            pos=0;
            memset(holder,'\0',50);
        }
    }
    strcpy(final,holder);
    printf("%s",final);
    pos=0;
    memset(holder,'\0',50);
    return 0;
}
