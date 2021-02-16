//
// Created by andru on 2/29/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structures and Pointers to structures.h"

/*
 * Hints :

    - char *name is a pointer, memory must be allocated by using malloc(3) to copy the string and return it.
    - Other useful commands: strcpy(3), strlen(3) and strcmp(3).
 */

typedef struct product {
    char *name;
    double price;
} product_t;

/*
 * @ptrProd != NULL
 * @return: the price of the product ptrProd
 */
double getPtrPrice(product_t *ptrProd){
    return ptrProd->price;
}

/*
 * @return: the price of the product prod
 */
double getPrice(product_t prod){
    return prod.price;
}

/*
 * ptrProd != NULL
 * @name in ptrProd != NULL
 * @return: a string on the heap that contains the name of the product ptrProd or NULL if an error happens
 */
char* getPtrName(product_t *ptrProd){
    char *nameptr = malloc(sizeof(char) * (strlen(ptrProd->name)+1));
    if (nameptr == NULL) {
        return NULL;
    }
    strcpy(nameptr, ptrProd->name);
    return nameptr;
}

/*
 * @name in prod != NULL
 * @return: a string on the heap that contains the name of the product ptrProd or NULL if an error happens
 */
char* getName(product_t prod){
    char *nameptr = malloc(sizeof(char) * (strlen(prod.name)+1));
    if (nameptr == NULL) {
        return NULL;
    }
    strcpy(nameptr, prod.name);
    return nameptr;
}

/*
 * @ptrProd != NULL
 * @name in ptrProd != NULL
 * @name in prod != NULL
 * @return: 1 if the two products are the same, i.e., they have the same price and the same name
 */
int prodEquals(product_t *ptrProd, product_t prod){
    if (strcmp(ptrProd->name, prod.name) == 0 && getPtrPrice(ptrProd) == getPrice(prod)) {
        return 1;
    }
    return 0;
}

int main_StructuresandPointers(){
    printf("marche sur inginious flemme de faire des tests ici");
    return 0;
}