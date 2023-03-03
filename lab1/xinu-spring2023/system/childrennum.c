/* childrennum.c - childrennum */

#include <xinu.h>

/* childrennum - return number of children a process has for lab 1 3.1d */

syscall childrennum(pid32 pid) {
	struct procent *prptr;
	intmask mask;

	mask = disable();
	if (isbadpid(pid) || pid == NULLPROC
		|| ((prptr = &proctab[pid])->prstate == PR_FREE)) {
		restore(mask);
		return SYSERR;
	}
	

	int childcount = prptr->pr_children;
	return childcount;
}
