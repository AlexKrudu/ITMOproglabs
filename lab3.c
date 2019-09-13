#include<stdio.h>

int main() {
    int num, temp, task5, inverted, temp2;
    printf("Enter octal number \n");
    scanf("%o", &num);
    printf("Decimal number: %d \n", num);
    temp = num >> 1;
    printf("%o >> 1 == %o\n", num, temp);
    inverted = ~num;
    printf("~ %o == %o(decimal) \n", num, inverted);
    printf("Enter octal number(task 5) \n");
    scanf("%o", &task5);
    temp2 = num ^ task5;
    printf("%o XOR %o == %o", num, task5, temp2);

    return 0;

}