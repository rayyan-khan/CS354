/* responsetime.c - responsetime */

/* new file for lab 3 3.2 */
#include <xinu.h>

syscall responsetime(pid32 pid) {

	if (isbadpid(pid)) {
		return (pri16) SYSERR;
	}

    struct	procent	*prptr = &proctab[pid];

    if (prptr->prctxswcount == 0) {
        return msclkcounter2 - prptr->prbeginready;
    }
    else if (prptr->prstate == PR_READY) {
        int32 temp = prptr->prresptime + (msclkcounter2 - prptr->prbeginready);
        return temp/(prptr->prctxswcount+1);
    }
    
    return (prptr->prresptime/prptr->prctxswcount);
   
}