#include "parallelogram.h"

float par_area(struct Parallelogram par){
    float result = par.side2 * par.height;
    return result;
}
float par_perimeter(struct Parallelogram par){
    float result = 2 * par.side1 + 2 * par.side2;
    return result;
}

//
// Created by alexa on 15.11.2019.
//

