//
// Created by andru on 3/11/2020.
//
#include "Protect.h"

#include <sys/param.h>
#include <pthread.h>

/*
 * For this first exercise concerning threads, you have to protect one variable from multiple concurrent accesses.
 * You don't have to create the threads, assume they already exist and
 * you must just protect the nb calls to the function "inc()"
 * that calls itself a global variable used by many different threads.
 * For this, use the mutex given as argument (you don't have to initialise it).
 * You can then only use these functions : pthread_mutex_lock(3) and pthread_mutex_unlock(3).
 */

/*
* Function used to protect a global variable used in the function inc().
*
* @inc : the function that must be called in critical (= protected) section
* @nb : the number of times the function inc() has to be called
* @mutex : an initialised mutex that has to be used for the protection
*
* @return 0 if no error, -1 otherwise
*/
int protect(void inc(void), int nb, pthread_mutex_t* mutex){
    if(pthread_mutex_lock(mutex) != 0) {return -1;}
    for (int i = 0; i < nb; i++) {
        inc();
    }
    if(pthread_mutex_unlock(mutex) != 0) {return -1;}
    return 0;
}