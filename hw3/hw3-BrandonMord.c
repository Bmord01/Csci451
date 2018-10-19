/*Brandon Mord
Csci 451 Hw 3 9/15/18

Compile Command : gcc -g hw3-BrandonMord.c -o hw3 -lpthread
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void *threadOne(void *arg){
    char *easy = "easy";
    int countEasy =0;
    char *p = ((char *) arg);
    int i;
    while((p=strstr(p,easy))!=NULL){
        p+=strlen(easy);
        countEasy++;
    }
    printf("Easy occurs %d Times\n",countEasy);
}

void *threadTwo(void *arg){
    char *polar = "polar";
    int countPolar =0;
    char *p = ((char *) arg);
    while((p=strstr(p,polar))!=NULL){
        p+=strlen(polar);
        countPolar++;
    }
    printf("Polar occurs %d Times\n",countPolar);
}

int main(){
    char *fileName = "hw3-data.txt";
    char *cmd = "wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt";
    int SIZE = 0;
    
    if(access(fileName,F_OK) == -1){
        system(cmd);
    }
    
    FILE *dataFile = fopen("hw3-data.txt","r");
    while(fgetc(dataFile) != EOF){
        SIZE++;
    }
    
    fclose(dataFile);
    
    int c;
    char *p = malloc((SIZE+1));
    size_t n = 0;
    
    dataFile = fopen("hw3-data.txt","r");
    while((c = fgetc(dataFile))!=-1){
        p[n++] = tolower((char) c);
    }
    fclose(dataFile);
    
    p[n]='\0';
    
    pthread_t tid;
    pthread_create(&tid,NULL,threadOne,((void *)p));
    pthread_create(&tid,NULL,threadTwo,((void *)p));
    pthread_join(tid,NULL);
    free(p);
    return 0;
}
