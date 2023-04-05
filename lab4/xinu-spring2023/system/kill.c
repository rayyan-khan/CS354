/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	int32	i;			/* Index into descriptors	*/

	/************ BEGIN CHANGES FOR LAB 4 PART 3**************/
	prptr = &proctab[pid];
	struct procent * prparentptr = &proctab[prptr->prparent];

	if (prptr->prparent != NULLPROC) {

		// check if child has children
		if(prptr->prchildcount != 0) {// if it does have children, update parent values to 0
			int k;
			for (k = 0; k < NPROC; k++) { // loop through children
				pid32 childpid = prptr->prchildpid[k]; // get PID of k'th child
				struct procent * prchildptr = &proctab[childpid]; // create pointer to that child
				prchildptr->prparent = 0;
			}
		}

		if (prparentptr->prchildstatus[pid] == 1) {
			prparentptr->prchildstatus[pid] = 3; // update child status
			prptr->prstate = PR_FREE; // copied these four lines of code from initialize.c to remove from proctab
			prptr->prname[0] = NULLCH;
			prptr->prstkbase = NULL;
			prptr->prprio = 0;
			resched();
		} 
		else if (prparentptr->prchildstatus[pid] == 2 && prptr->prstate == PR_CURR) {
			prparentptr->prstate = PR_READY; // set prparent to PR_READY
			prparentptr->prchildstatus[pid] = 4; // update child status
			ready(prptr->prparent); // add parent to readylist
		}
	}

	// set global variable of callback function
	void * callback_glbl = prptr->callback_glbl;
	
	/****************** END CHANGES FOR LAB 4 PART 3 ***************/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr->prstate) == PR_FREE) { // modified due to initializing prptr above
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
