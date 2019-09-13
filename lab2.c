#include<stdio.h>
#include<math.h>

int main2() {
    double alpha, beta, z1, z2;
    printf("Enter alpha(radians) \n");
    scanf("%lf", &alpha);
    printf("Enter beta(radians) \n");
    scanf("%lf", &beta);
    z1 = (sin(alpha) + cos(2 * beta - alpha))/(cos(alpha) - sin(2 * beta - alpha));
    z2 = (1 + sin(2 * beta))/(cos(2 * beta));
    printf("Z1 = %lf \n", z1);
    printf("Z2 = %lf", z2);
    return 0;
}