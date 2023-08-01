/* cbwallxregister.c - cbwallxregister*/

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cbwallxregister -- register callback functions
 *------------------------------------------------------------------------
 */
syscall cbwallxregister(void (* cbf) (void), uint32 wallthr) {

    // kprintf("cbf value: %d\ntext value: %d\nextext value: %d\n", (uint32)&cbf, (uint32)&text, (uint32)&etext);

    // if (wallthr < 0 || wallthr > 8000) { // out of threshold range
    //     kprintf("CASE 1 SYSERR\n");
    //     return SYSERR;
    // }
    if (((uint32)cbf < (uint32)&text) || ((uint32)cbf > (uint32)&etext)) { // out of range of text
        // kprintf("CASE 2 SYSERR\n");
        return SYSERR;
    }
    if (msclkcounter1 > wallthr) {
        // kprintf("CASE 3 SYSERR\n");
        return SYSERR;
    }
    
    struct procent * prptr = &proctab[getpid()]; // get a pointer to the current process
    prptr->prwallxcallback = cbf;
    prptr->prwallxthr = wallthr;
    return 0;
}