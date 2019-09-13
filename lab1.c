#include<stdio.h>

int main1() {
    char str[100];
    int num;
    printf("Enter string \n");
    scanf("%s", str);
    printf("Enter number \n");
    scanf("%d", &num);
    printf("Entered string is %s \n", str);
    printf("Entered number is %d \n", num);
    return 0;

}
