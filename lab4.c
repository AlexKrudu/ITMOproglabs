#include <stdio.h>

int main(void) {
  int num, remnant;
  printf("Enter number(octal) \n");
  scanf("%o", &num);
  if (num >= 64 && num <= 87){
    printf("Number is in range \n");
  }
  else{
    printf("Number is not in range \n");
  }
  remnant = num/4096;
  if (num/4096 % 2 == 0){
      printf("13rd bit is 0");
  }  
  else{
    printf("13rd bit is 1");
  }
}
