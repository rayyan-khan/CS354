/* cbcpuxregister.c - cbcpuxregister */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbcpuxregister -- register callback functions
 *------------------------------------------------------------------------
 */
syscall cbcpuxregister(void (* cbf) (void), uint32 cputhr) {

    // kprintf("cbf value: %d\ntext value: %d\nextext value: %d\n", (uint32)&cbf, (uint32)&text, (uint32)&etext);

    if (cputhr < 0 || cputhr > 8000) { // out of threshold range
        //kprintf("CASE 1 SYSERR\n");
        return SYSERR;
    }
    if ((cbf < (uint32)&text) || (cbf > (uint32)&etext)) { // out of range of text
        // kprintf("CASE 2 SYSERR\n");
        return SYSERR;
    }

    struct procent * prptr = &proctab[getpid()]; // get a pointer to the current process
    prptr->prcallback = cbf;
    prptr->prcputhr = cputhr;
    return 0;
}