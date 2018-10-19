/*
    Brandon Mord
    Csci 451 Hw 4
    9/23/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

bool reading = true;
bool printable = false;
pthread_mutex_t lock;
pthread_t tid[2];
pthread_cond_t handled;
int number=0;

void* Producer(void * arg){
    pthread_mutex_lock(&lock);
    FILE *inpt = fopen("hw4.in","r");
    while((fscanf(inpt,"%d\n",&number))!= EOF){
        printable = true;
        pthread_mutex_unlock(&lock);
        pthread_cond_wait(&handled,&lock);
    }
    pthread_mutex_unlock(&lock);
    reading=false;
    fclose(inpt);
    return NULL;
}

void* Consumer(void *arg){
    FILE *out = fopen("hw4.out","w");
    do{
        pthread_mutex_lock(&lock);
        if(printable){
            if(number % 2 == 0){
                fprintf(out,"%d\n",number);
                fprintf(out,"%d\n",number);
            }
            else{
                fprintf(out,"%d \n",number);
            }
            printable=false;
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&handled);        
    }while(reading);
    fclose(out);
    return NULL;
}

int main(){
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&handled,NULL);
    pthread_create(&(tid[0]),NULL,Producer,NULL);
    pthread_create(&(tid[1]),NULL,Consumer,NULL);
    
    int i;
    
    for(i=0;i<2;i++){
        pthread_join(tid[i],NULL);
    }
    return 0;
}
