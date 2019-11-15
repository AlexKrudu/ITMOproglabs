#include <stdio.h>
#include <string.h>

int main8(void) {
    char string1[128];
    char string2[128];
    int n, result = -1;
    scanf("%s", &string1);
    scanf("%s", &string2);
    scanf("%d", &n);
    printf("%s \n", strncat(string1, string2, 128)); // Конкатенация строк
    scanf("%s", &string1); // ввод первой строки заново, т.к она поменялась
    for (int i = 0; i < n; i++) { // Можно было бы заюзать strcmp, но я не хочу
        if (string1[i] != string2[i]) {
            result = string1[i] < string2[i];
            break;
        }
    }
    printf("%d \n", result); // 1 - первая меньше, 0 - первая больше, -1 - равны
    printf("%d \n", strlen(string1)); // Длины строк
    printf("%d \n", strlen(string2));
    printf("%c \n",
           *strpbrk(string1, string2)); // поиск в одной строке любого из множества символов, входящих во вторую строку
    printf("%d \n", strcspn(string1, string2)); // длина отрезка одной строки, не содержащей символы второй строки


}
//
// Created by alexa on 18.10.2019.
//

