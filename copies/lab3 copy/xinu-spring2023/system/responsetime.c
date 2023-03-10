/* responsetime.c - responsetime */

/* new file for lab 3 3.2 */
#include <xinu.h>

syscall responsetime(pid32 pid) {

	if (isbadpid(pid)) {
		return (pri16) SYSERR;
	}

    struct	procent	*prptr = &proctab[pid];

    // kprintf("PID: %d CTXSW: %d RESPTIME: %d prbeginready: %d\n", pid, prptr->prctxswcount, prptr->prresptime, prptr->prbeginready);

    if (prptr->prctxswcount == 0 && prptr->prstate == PR_READY) {
        return msclkcounter2 - (prptr->prbeginready);
    }
    else if (prptr->prstate == PR_READY) {
        int32 temp = prptr->prresptime + (msclkcounter2 - prptr->prbeginready);
        return temp/(prptr->prctxswcount + 1);
    }
    
    return (prptr->prresptime/prptr->prctxswcount);
   
}