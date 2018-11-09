/************************************************/
/* Produces a character once every 120 seconds. */
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
       for (i = 58; i < 127; i++) {
           output = fopen("./output3.txt", "w");
           fprintf(output, "%c\n", i);
           fclose(output);
           sleep(120);
       }
    }
    return 1;
}
