/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		ptold->prctxswcount = ptold->prctxswcount + 1;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;

	/* below section for lab 3 3.2 */ 
	uint32 diff = msclkcounter2 - ptnew->prbeginready;
	if (diff = 0) {
		diff = 1;
	}
	ptnew->prresptime = diff; 
	/* end 3.2 section */

	preempt = QUANTUM;		/* Reset time slice for process	*/

	#if DYSCHEDENABLE
	/* below section for lab 3 4.2 - check value of preempt to determine CPU-bound or IO-bound */
	if (preempt == 0) // then it is CPU-bound
	{
		// update ptold
		ptold->prprio = xdynprio[ptold->prprio].xtqexp;
	}
	else {
		ptold->prprio = xdynprio[ptold->prprio].xslpret;
	}

	/* update time slice - get new time slice value based on priority */
	preempt = xdynprio[ptnew->prprio].xquantum;

	#endif

	/* end 4.2 section */

	ptold->prcpu = ptold->prcpu + currcpu; // add for lab 3 3.1, update prcpu

	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	currcpu = 0; // add for lab 3 3.1, reset currcpu


	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
