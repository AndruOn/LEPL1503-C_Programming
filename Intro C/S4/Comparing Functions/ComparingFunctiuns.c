//
// Created by andru on 3/3/2020.
//

#include "ComparingFunctiuns.h"

#include <stdio.h>

//forme de f1 et f2 uint8_t func(uint8_t n)
int cmp_func(u_int8_t (*ptrf1) (int), u_int8_t (*ptrf2) (int)){
    for (u_int8_t i = 0; i < 255; i++) {
        if ((ptrf1)(i) != (ptrf2)(i)) {
            return 0;
        }
    }
    return 1;
}

int main_ComparingFunctiuns(){
    printf("Main de Comparing Functiuns:\n");
    return 0;
}