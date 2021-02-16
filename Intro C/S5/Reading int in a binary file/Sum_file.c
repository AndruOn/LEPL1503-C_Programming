//
// Created by andru on 3/11/2020.
//

#include "Sum_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy(3)
#include <fcntl.h> //open(2)
#include <unistd.h> //fruncate(3)
#include <sys/mman.h> //mmap(6) msync(3) munmap(2)



/*
 *  You can only use open(2), mmap(2), munmap(2), fstat(2) and close(2).
 *  Hint : fstat(2) is mandatory to know the size of the file and thus with a simple formula,
 *          the number of integers that are stored in it (find it !).
 *
 * @pre filename != NULL, name of the file
 * @post returns the sum of all integers stored in the binary file.
 *       return -1 if the file can not be open.
 *       return -2 if the file can not be closed.
 *       return -3 if mmap() fails.
 *       return -4 if munmap() fails.
 *       return -5 if fstat() fails.
 */
int sum_file(char *filename) {
    int filedes = open(filename, O_RDONLY);
    if (filedes == -1) {
        return -1;
    }
    struct stat* buf = malloc(sizeof(struct stat));
    if (fstat(filedes, buf) == -1) {
        if (close(filedes) == -1) {return -2;}
        return -5;
    }
    size_t sizeofFile = buf->st_size;
    if (sizeofFile == 0) {
        if (close(filedes) == -1) {return -2;}
        return 0;
    }
    int *ptrfile = mmap(NULL, sizeofFile, PROT_READ, MAP_SHARED, filedes, 0);
    if (ptrfile == MAP_FAILED) {
        if (close(filedes) == -1) {return -2;}
        return -3;
    }

    int total = 0;
    for (int i = 0; i < sizeofFile/sizeof(int); i++) {
        total += *(ptrfile++);
    }

    if (munmap(ptrfile, sizeofFile) == -1){
        if (close(filedes) == -1) {return -2;}
        return -4;
    }
    if (close(filedes) == -1) {return -2;}
    return total;
}