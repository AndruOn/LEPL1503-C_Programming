//
// Created by andru on 3/11/2020.
//

#include "SortmyPoints.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy(3)
#include <fcntl.h> //open(2)
#include <unistd.h> //fruncate(3)
#include <sys/mman.h> //mmap(6) msync(3) munmap(2)

typedef struct points {
    int NOMA;
    float LEPL1103;
    float LEPL1203;
    float LEPL1108;
    float LEPL1302;
    float LEPL1402;
    float average;
} points_t;

/*
* Function used to compare two structures based on their averages.
*
* @s1 : a pointer to the first structure
* @s2 : a pointer to the second structure
*
* @return an integer less than, equal to, or greater than zero if the first argument is considered to be
*        respectively less than, equal to, or greater than the second
*/
int compar(const void* s1, const void* s2){
    float diff = ((points_t*)s1)->average - ((points_t*)s2)->average;
    if (diff > 0){
        return 1;
    } else if (diff == 0){
        return 0;
    } else{
        return -1;
    }
}


/*
 * Now, implement a function that will allow us to read the file,
 * sort the array and then write the sorted structures back to the file.
 * For this, you can only use these functions :
 *              open(2), mmap(2), munmap(2), msync(2), fstat(2) and close(2).
 * The file will always exist and will always contain at least one structure.
 * You can use your compare function previously done.

Hint : if you are not familiar with theses functions, please do or redo the exercices about files.

Hint : There is certainly a built-in function that can be used to sort the array mapped with mmap.
 */

/*
* Function used to update the file with the structures stored in it
*
* @filename : the path indicating where to find the file (!= NULL)
*
* @return 0 if no error
*        -1 if open failed
*        -2 if mmap failed
*        -3 if munmap failed
*        -4 if msync failed
*        -5 if fstat failed
*        -6 if close failed
*/
int sort(char* filename){
    int filepath, fsize, nbelem;
    struct stat buf;
    points_t *ptrfile;
    //open
    if ((filepath = open(filename, O_RDWR)) == -1){return -1;}
    //get info on file
    if (fstat(filepath, &buf) == -1){
        if(close(filepath) == -1){return -6;}
        return -5;
    }
    fsize = buf.st_size;
    nbelem = fsize/ sizeof(points_t);
    //map memory to file
    if ((ptrfile = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, filepath, 0)) == MAP_FAILED){
        if(close(filepath) == -1){return -6;}
        return -2;
    }
    //get average
    for (int i = 0; i < nbelem; ++i) {
        (ptrfile+i)->average = ((ptrfile+i)->LEPL1103 + (ptrfile+i)->LEPL1108 + (ptrfile+i)->LEPL1203 +
                (ptrfile+i)->LEPL1302 + (ptrfile+i)->LEPL1402) / 5;
    }
    //sort array
    qsort(ptrfile, nbelem, sizeof(points_t), compar);
    //sync
    if (msync(ptrfile, fsize, MS_SYNC) == -1){
        if (munmap(ptrfile, fsize) == -1){
            if(close(filepath) == -1){return -6;}
            return -3;
        }else{
            if(close(filepath) == -1){return -6;}
            return -4;
        }
    }
    if (munmap(ptrfile, fsize) == -1){
        if(close(filepath) == -1){return -6;}
        return -3;
    }
    if (close(filepath) == -1){return -6;}
    return 0;
}