/* cbchildregister.c - cbchildregister */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbchildregister - register a callback function for a new processz
 *------------------------------------------------------------------------
 */

void 	*callback_glbl; 
syscall cbchildregister(void (*cbf)(void)) {
    struct procent * prptr = &proctab[getpid()]; // get a pointer to the current process

    if(prptr->prcallback == NULL) {   
        prptr->prcallback = cbf;
    }
    else {
        return SYSERR;
    }

    return 0;
}