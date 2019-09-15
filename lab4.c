#include <stdio.h>

int main4(void) {
  int num, remnant;
  printf("Enter number(octal) \n");
  scanf("%o", &num);
  printf("%d (1 - in range, 0 - not in range)\n", ((num- 87) >> 31) * ((64 - num) >> 31));
  remnant = num/4096;
  printf("13rd bit is %d",num/4096 % 2);
}
