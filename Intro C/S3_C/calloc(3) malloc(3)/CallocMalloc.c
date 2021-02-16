//
// Created by andru on 2/29/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "CallocMalloc.h"


char *buf_strcpy(const char *src) {
    if (strlen(src) == 0) {
        return NULL;
    }
    char *dest = malloc(sizeof(char)*(strlen(src) + 1));
    char* returnbuf = dest;
    if (dest == NULL){
        return NULL;
    }
    //src = "cafcafcaffca";
    while (*src != '\0') {
        *dest = *src;
        dest++; src++;
    }
    *dest = '\0';
    return returnbuf;
}


void* calloc2(size_t nmemb, size_t size) {
    if ((nmemb == 0) | (size == 0)) {
        return NULL;
    }
    size_t *array = malloc(nmemb * size);
    if (array == NULL) {return NULL;}
    for (int i = 0; i < nmemb ; i++) {
        array[i] = 0;
    }
    return array;
}


void *sleepy_malloc(size_t s) {
    void* memory = malloc(s);
    int i = 1;
    while (memory == NULL) {
        sleep(5);
        memory = malloc(s);
        if (++i == 10){return NULL;}
    }
    return memory;
}

int main_CallocMalloc(){
    printf("deja fait des tests oublié de le sauver");
    return 0;
}