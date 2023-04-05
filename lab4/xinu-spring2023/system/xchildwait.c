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

    // kprintf("PID IN XCHILDWAIT: %d BLOCK VALUE: %d\n", pid, block);

	if (block == 0) { /* blocking call*/ 
        if (pid <= 0 || isbadpid(pid)) {
            // kprintf("HITS CASE 1\n");
            return SYSERR;
        }
        prparentptr->prstate = PR_CHLDWAIT; // set parent to PR_CHLDWAIT
        prparentptr->prchildstatus[pid] = 2; // set child status to 2
        ready(pid); // add it back to the ready list
        return pid;
    }
    else if (block == 1) { /* nonblocking call */
        // kprintf("IN LINE 27\n");
        if (prparentptr->prchildstatus[pid] == 3) {
            // kprintf("IN LINE 29\n");
            prparentptr->prchildstatus[pid] = 4; // set child status to 2
            
            if (pid > 0) {
                // kprintf("HITS CASE 2\n");
                return pid;
            }
        }
    }

    // kprintf("HITS CASE 3\n");
    return  SYSERR;
}
