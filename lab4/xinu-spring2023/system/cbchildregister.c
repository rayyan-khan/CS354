/* cbchildregister.c - cbchildregister */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbchildregister - register a callback function for a new processz
 *------------------------------------------------------------------------
 */
extern syscall cbchildregister(void (*cbf)(void)) {
    struct procent * prptr = &proctab[getpid()]; // get a pointer to the current process
    prptr->prcallback = cbf;
}