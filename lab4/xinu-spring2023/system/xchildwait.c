/* xchildwait.c - xchildwait */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  xchildwait - lab 4 assignment blocking function 
 *------------------------------------------------------------------------
 */
syscall	xchildwait(uint32 block, pid32 pid)
{
    struct procent * prptr = &proctab[pid];
    struct procent * prparentptr = &proctab[prptr->prparent]; // get pointer to parent

    if (pid <= 0 || isbadpid(pid)) {
            kprintf("HITS CASE 1\n");
            return SYSERR;
    }

	if (block == 0) { /* blocking call*/ 
        prparentptr->prstate = PR_CHLDWAIT; // set parent to PR_CHLDWAIT
        prparentptr->prchildstatus[pid] = 2; // set child status to 2
        ready(pid); // add it back to the ready list
    }
    else if (block == 1) { /* nonblocking call */
        if (prparentptr->prchildstatus[pid] == 3) {
            prparentptr->prchildstatus[pid] = 4; // set child status to 2
            
            if (pid > 0) {
                kprintf("HITS CASE 2\n");
                return pid;
            }
        }
    }

    kprintf("HITS CASE 3\n");
    return  SYSERR;
}
