/************************************************/
/* Produces an even value once every second.    */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void) {
int i;
char number;
FILE *output;
    while (1) {
       for (i = 0; i < 10; i+=2) {
           output = fopen("./output2.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           sleep(1);
       }
    }
    return 1;
}
