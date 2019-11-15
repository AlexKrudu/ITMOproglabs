#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    FILE *f = fopen(filename, "w");
    if (f == NULL) printf("error");
    else printf("done");
    char* in1 = argv[2];
    char* in2 = argv[3];
    int num1 = atoi(in1);
    int num2 = atoi(in2);
    int result = num1 + num2;
    fprintf(f, "%d - result of adding", result);
    fclose(f);
}
//
// Created by alexa on 15.11.2019.
//

