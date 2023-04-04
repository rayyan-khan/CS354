/* xchildwait.c - xchildwait */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  xchildwait - lab 4 assignment blocking function 
 *------------------------------------------------------------------------
 */
syscall	xchildwait(uint32 block, pid32 pid)
{
    struct procent * prptr = &proctab[pid];
	if (block == 0) {
        prptr->prparent->prstate = PR_CHLDWAIT; // set parent to PR_CHLDWAIT
        prptr->prparent->prchildstatus[pid] = 2; // set child status to 2
        resched(); // allows the child process to run
    }
    else if (block == 1) {
        if (prptr->prparent->prchildstatus[pid] = 3) {
            prptr->prparent->prchildstatus[pid] = 2; // set child status to 2
        }
    }
}
