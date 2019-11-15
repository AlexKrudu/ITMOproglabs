#include <stdio.h>
#include "parallelogram.h"


int main11(){
    struct Parallelogram para;
    scanf("%f %f %f",&para.side1, &para.side2, &para.height);
    printf("Perimeter: %f\n", par_perimeter(para));
    printf("Area: %f", par_area(para));
    return 0;
};
//
// Created by alexa on 15.11.2019.
//

