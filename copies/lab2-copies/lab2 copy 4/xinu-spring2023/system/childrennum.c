/* childrennum.c - childrennum */

#include <xinu.h>

/* childrennum - return number of children a process has for lab 1 3.1d */
/* lab 2 4.2 as well */

syscall childrennum(pid32 pid) {
	struct procent *prptr;

	//kprintf("IN CHILDRENNUM"); // debugging

	if (isbadpid(pid) || pid == NULLPROC
		|| ((prptr = &proctab[pid])->prstate == PR_FREE)) {
		return SYSERR;
	}
	
	int childcount = prptr->pr_children; 
	//kprintf("IN CHILDRENNUM, PID %d, CHILDREN %d\n", pid, childcount); // debugging
	return childcount;
}
