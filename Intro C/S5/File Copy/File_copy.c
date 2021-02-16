//
// Created by andru on 3/11/2020.
//

#include "File_copy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy(3)
#include <fcntl.h> //open(2)
#include <unistd.h> //fruncate(3)
#include <sys/mman.h> //mmap(6) msync(3) munmap(2)

/*
Given a file containing arbitrary bytes, you must write a function that copies the file. Obviously,
your function cannot modify the content of the original file.
Beware that the copied file should have the same permissions as the original file.

Use only open(2), mmap(2), munmap(2), msync(2), ftruncate(3), fstat(2), memcpy(3) and close(2). You can call memcpy(3) only once.

Hint : msync(2) is a function that ensures that your modifications done in memory
     (so in the address returned by mmap) will also be saved in the file.
     Check the documentation to learn how to use it (pay attention to the flags).
     Call it before munmap() (or your modifications to the memory may be lost) !

Hint : The function ftruncate(3) is a function that you won't need to use frequently.
     However, this function is mandatory to pass this exercice !
     In your code, you have to use it to extend the size of the file you opened for copying the original one.
     When you'll call open (with the appropriate flags to meet the requirements above),
     the size of the new file freshly created will be set to zero.
     So, in order for the mmap function to work, you'll need to extend its size to the one you want by calling ftruncate.
     Read the documentation linked and use this trick BEFORE calling mmap !

Hint : Permissions are sometimes hard to deal with. Be aware that, when using mmap with MAP_SHARED and PROT_WRITE,
     your file descriptor argument must have been opened with the O_RDWR flag.
     You need to read the file to copy it in memory and you ask to write in this piece of memory
     (with the PROT_WRITE) so you also need the write permission on the file !
*/

/*
 * @pre file_name != NULL, name of the original file
 *      new_file_name != NULL, name of the new file (the copy)
 *
 * @post copy the contents of {file_name} to {new_file_name}.
 *       return 0 if the function terminates with success, -1 in case of errors.
 */
int copy(char *file_name, char *new_file_name) {
    //open READfile
    int fileREAD = open(file_name, O_RDONLY);
    if (fileREAD == -1) {return -1;}
    //check size
    struct stat* buf = malloc(sizeof(struct stat));
    if (fstat(fileREAD, buf) == -1) {
        close(fileREAD);
        return -1;
    }
    //create WRITEfile
    int fileWR = open(new_file_name, O_RDWR | O_CREAT, buf->st_mode);
    if (fileWR == -1) {
        close(fileREAD);
        return -1;
    }
    size_t sizeofFile = buf->st_size;
    //ftruncate WRITEfile to READfile size
    if (ftruncate(fileWR, sizeofFile) == -1){
        close(fileREAD);close(fileWR);
        return -1;
    }
    //Map memory READ
    char *ptrfileRead = mmap(NULL, sizeofFile, PROT_READ, MAP_SHARED, fileREAD, 0);
    if (ptrfileRead == MAP_FAILED) {
        close(fileREAD);close(fileWR);
        return -1;
    }
    //Map memory WR
    char *ptrfileWR = mmap(NULL, sizeofFile, PROT_WRITE, MAP_SHARED, fileWR, 0);
    if (ptrfileWR == MAP_FAILED) {
        close(fileREAD);close(fileWR);
        return -1;
    }
    //Copy from READfile to WRfile
    memcpy(ptrfileWR, ptrfileRead, sizeofFile);
    //msync Map WR
    if (msync(ptrfileWR, sizeofFile, MS_SYNC) == -1) {
        close(fileREAD);close(fileWR);
        return -1;
    }
    //UnMap READ
    if (munmap(ptrfileRead, sizeofFile) == -1) {
        close(fileREAD);close(fileWR);
        return -1;
    }
    //UnMap WR
    if (munmap(ptrfileWR, sizeofFile) == -1) {
        close(fileREAD);close(fileWR);
        return -1;
    }
    //Close all files
    if (close(fileREAD) == -1) {return -1;}
    if (close(fileWR) == -1) {return -1;}
    return 0;
}

