/* clkhandler.c - clkhandler */

#include <xinu.h>
extern void * callback_glbl;

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */

volatile uint32 currcpu = 0;
uint32 use_callback = 0;
uint32 use_wallx = 0;
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	msclkcounter1++;

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* lab 5 code */
	currcpu++; // lab 3 3.1
	struct procent * prptr = &proctab[getpid()];

	if(cpuusage(getpid()) > prptr->prcputhr && prptr->prcputhr > 0) {
		callback_glbl = prptr->prcallback; // set value to callback global variable
		use_callback = 1;
		prptr->prcputhr = 0;
	}
	if(cpuusage(getpid()) > prptr->prcputhr && prptr->prcputhr > 0) {
		wallx_glbl = prptr->prwallxcallback; // set value to callback global variable
		use_wallx = 1;
		prptr->prwallxthr = 0;
	}

	/* end lab 5 code */

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
