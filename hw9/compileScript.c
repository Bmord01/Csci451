#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    system("gcc -g program1.c -o p1");
    system("gcc -g program2.c -o p2");
    system("gcc -g program3.c -o p3");
    system("gcc -g program4.c -o master -lpthread");
    return 0;
}
