//
// Created by andru on 3/11/2020.
//

#include "Get_Set_on_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy(3)
#include <fcntl.h> //open(2)
#include <unistd.h> //fruncate(3)
#include <sys/mman.h> //mmap(6) msync(3) munmap(2)

/*
 * Given a file containing a large array of integers, you have to write a function to edit the element
 * at a given index in the array and another function to retrieve a specific element from this array.

Use only open(2), mmap(2), munmap(2), msync(2), fstat(2) and close(2).

Hint : msync(2) is a function that ensures that your modifications done in memory
 (so in the address returned by mmap) will also be saved in the file.
 Check the documentation to learn how to use it (pay attention to the flags).
 Call it before munmap() (or your modifications to the memory may be lost) !
 */



/*
* @pre filename != NULL, index >= 0
* @post return the integer at the index {index}
*       of the array in the file {filename}.
*       return -1 in case of error.
*       return -2 if index >= length of array.
*/
int get(char *filename, int index) {
    int filedes = open(filename, O_RDONLY);
    if (filedes == -1) {
        return -1;
    }
    struct stat* buf = malloc(sizeof(struct stat));
    if (fstat(filedes, buf) == -1) {
        close(filedes);
        return -1;
    }
    size_t sizeofFile = buf->st_size;
    size_t nbrofInt = sizeofFile / sizeof(int);
    if (index >= nbrofInt) {
        if (close(filedes) == -1) {return -1;}
        return -2;
    }
    int *ptrfile = mmap(NULL, sizeofFile, PROT_READ, MAP_SHARED, filedes, 0);
    if (ptrfile == MAP_FAILED) {
        close(filedes);
        return -1;
    }

    int returnVal;
    int i = 0;
    while (i != index){
        ptrfile++; i++;
    }
    returnVal = *ptrfile;
    if (munmap(ptrfile, sizeofFile) == -1){
        close(filedes);
        return -1;
    }
    if (close(filedes) == -1) {return -1;}
    return returnVal;
}

/*
 * @pre filename != NULL, index >= 0
 * @post set the element in the file {filename}
 *       at index {index} at value {value}.
 *       do nothing in case of errors
 */
void set(char *filename, int index, int value) {
    int filedes = open(filename, O_RDWR);
    if (filedes == -1) {
        return;
    }
    struct stat* buf = malloc(sizeof(struct stat));
    if (fstat(filedes, buf) == -1) {
        close(filedes);
        return;
    }
    size_t sizeofFile = buf->st_size;
    size_t nbrofInt = sizeofFile / sizeof(int);
    if (index >= nbrofInt) {
        close(filedes);
        return;
    }
    int *ptrfile = mmap(NULL, sizeofFile, PROT_READ|PROT_WRITE, MAP_SHARED, filedes, 0);
    if (ptrfile == MAP_FAILED) {
        close(filedes);
        return;
    }

    int i = 0;
    while (i != index){
        ptrfile++; i++;
    }
    *ptrfile= value;
    if (msync(ptrfile, sizeofFile, MS_SYNC) == -1){
        close(filedes);
        return;
    }
    if (munmap(ptrfile, sizeofFile) == -1){
        close(filedes);
        return;
    }
    close(filedes);
}