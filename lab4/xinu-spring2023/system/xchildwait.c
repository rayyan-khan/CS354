/* xchildwait.c - xchildwait */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  xchildwait - lab 4 assignment blocking function 
 *------------------------------------------------------------------------
 */
syscall	xchildwait(uint32 block, pid32 pid)
{
    struct procent * prptr = &proctab[pid];
    struct procent * prparentptr = prptr->prparent; // get pointer to parent
	if (block == 0) {
        prparentptr->prstate = PR_CHLDWAIT; // set parent to PR_CHLDWAIT
        prparentptr->prchildstatus[pid] = 2; // set child status to 2
        resched(); // allows the child process to run
    }
    else if (block == 1) {
        if (prparentptr->prchildstatus[pid] = 3) {
            prparentptr->prchildstatus[pid] = 2; // set child status to 2
        }
    }
}
