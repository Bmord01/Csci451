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
    int rule1=0,rule2=0;
    char a='a',y='y',r='r';
    char newLine = '\n';
    files[0]=open("temp1.data",0666);
    files[1] = creat("temp2.data",0666);
    files[2] = creat("shared1.dat",0666);
    files[3] = creat("shared2.dat",0666);
    
    bool first = true;
    bool con=false,vow=false;
    char in,hold=0,hold2=0;
    while(read(files[0],&in,1)!=0){
        if(first){
            if(in == 'a' || in == 'e' || in == 'i' || in == 'o' || in == 'u'|| in == 'A' || in == 'E' || in == 'I' || in == 'O' || in == 'U'){
                rule1++;
                write(files[1],&in,1);
                vow=true;
            }
            else{
                rule2++;
                hold = in;
                con=true;
            }
            first = false;  
            
        }
        else{
            if(in == '\n'){
                if(con){
                    write(files[1],&hold,1);
                    write(files[1],&a,1);
                    write(files[1],&y,1);
                    if(hold2!=0){
                        write(files[1],&hold2,1);
                        hold2=0;
                    }
                    write(files[1],&newLine,1);
                }
                else if(vow){
                    write(files[1],&r,1);
                    write(files[1],&a,1);
                    write(files[1],&y,1);
                    if(hold2!=0){
                        write(files[1],&hold2,1);
                        hold2=0;
                    }
                    write(files[1],&newLine,1);
                }
                con=false;
                vow=false;
                first=true;
            }
            else{
                if(in<65 || (in>90 && in<97) || in>122){
                    hold2=in;
                }
                else{
                    write(files[1],&in,1);
                }
            }
        }
    }
    
    char s1 = rule1 + '0';
    char s2 = rule2 + '0';
    
    write(files[2],&s1,1);
    write(files[3],&s2,1);
    
    int i;
    for(i=0;i<4;i++){
        close(files[i]);
    }
    return 0;
}
