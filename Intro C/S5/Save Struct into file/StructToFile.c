//
// Created by andru on 3/10/2020.
//
#include "StructToFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy(3)
#include <fcntl.h> //open(2)
#include <unistd.h> //fruncate(3)
#include <sys/mman.h> //mmap(6) msync(3) munmap(2)

/*
 * Use only open(2), close(2), mmap(2), munmap(2), msync(2), memcpy(3) and ftruncate(3).
 You can only call memcpy(3) once.

Hint : read carefully the man page of open(2) to manage all the cases mentionned above.
 Be sure to open the file with the appropriate rights.

Hint : msync(2) is a function that ensures that your modifications done
 in memory (so in the address returned by mmap) will also be saved in the file.
 Check the documentation to learn how to use it (pay attention to the flags).
 Call it before munmap() (or your modifications to the memory may be lost) !

Hint : The function ftruncate(3) is a function that you won't need to use frequently.
 However, this function is mandatory to pass this exercice !
 In your code, you have to use it to extend the size of the file you opened.
 When you'll call open (with the appropriate flags to meet the requirements above), the size of the file will be set to zero.
 So, in order for the mmap function to work, you'll need to extend its size to the one you want by calling ftruncate.
 Read the documentation linked and use this trick BEFORE calling mmap !

 Hint : size is the length of the array but not the total number
 of bytes of what you want to save into your file (because point_t structures doesn't have a size of one byte).
 To know the total size of your array (in terms of bytes used), you'll need the function sizeof() !
*/


typedef struct point {
    int x;
    int y;
    int z;
} point_t;

static void print_point_t(point_t* p_ptr){
    printf("point_t:  x:%d y:%d z:%d\n", p_ptr->x, p_ptr->y, p_ptr->z);
}


/*
 * @pre pt != NULL, pointer to the first point_t in the array
 *      size > 0, the length of the array.
 *      filename != NULL
 * @post writes the array of point_t in the file.
 *       return 0 is everything worked correctly
 *       -1 if open() failed.
 *       -2 if close() failed.
 *       -3 if mmap() failed.
 *       -4 if munmap() failed.
 *       -5 if msync() failed.
 *       -6 if ftruncate() failed.
 */
static int save(point_t *pt, int size, char *filename) {
    size_t sizeofArray = sizeof(point_t) * size;
    int filedes = open(filename, O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
    if (filedes == -1) {
        close(filedes);
        return -1;
    }
    if (ftruncate(filedes, sizeofArray) == -1){
        if (close(filedes) == -1) {return -2;}
        return -6;
    }
    point_t *ptrfile = mmap(NULL, sizeofArray, PROT_WRITE|PROT_READ, MAP_SHARED, filedes, 0);
    if (ptrfile == MAP_FAILED){
        if (close(filedes) == -1) {return -2;}
        return -3;
    }
    memcpy(ptrfile, pt, sizeofArray);
    if (msync(ptrfile, sizeofArray, MS_SYNC)<0){
        if (close(filedes) == -1) {return -2;}
        return -5;
    }
    if (munmap(ptrfile, sizeofArray)<0){
        if (close(filedes) == -1) {return -2;}
        return -4;
    }
    if (close(filedes) == -1) {return -2;}
    return 0;
}




int main_StructToFile(){
    printf("Main de StructToFile:\n");
    point_t *p = malloc(sizeof(point_t));
    p->x = 1; p->y = 2; p->z = 3;
    print_point_t(p);
    return 0;
}
