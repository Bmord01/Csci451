/************************************************/
/* Produces an odd value once every 30 seconds. */
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
       for (i = 1; i < 10; i+=2) {
           output = fopen("./output1.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           sleep(30);
       }
    }
    return 1;
}
