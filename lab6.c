#include <stdio.h>
#include <malloc.h>

int main(void){
    int n = 5;
    char *arr = (char *) _alloca(n * sizeof(char));
    arr[0] = 'H';
    arr[1] = 'e';
    arr[2] = 'l';
    arr[3] = 'l';
    arr[4] = 'o';
    for (int i = 0; i < n; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
    char *array;
    array = (char*)malloc(n);
    array[0] = 'H';
    array[1] = 'e';
    array[2] = 'l';
    array[3] = 'l';
    array[4] = 'o';
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;


}
//
// Created by alexa on 27.09.2019.
//