/* cpuusage.c - cpuusage */

/* new file for lab 3 3.1 */
#include <xinu.h>

syscall cpuusage(pid32 pid) {

	if (isbadpid(pid)) {
		return (pri16) SYSERR;
	}

    struct	procent	*prptr = &proctab[pid];
    
    if (prptr->prstate == PR_CURR) {
        return prptr->prcpu + currcpu;
    }
    return prptr->prcpu;
}