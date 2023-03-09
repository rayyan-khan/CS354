/* iobnd.c - iobnd */

/* new file for lab 3 4.4 */
#include <xinu.h>

void iobnd(void) {
    while(msclkcounter2 <= STOPPINGTIME) {
        int i;
        for (i = 0; i < 150000; i++) {
        }
        sleepms(80);
    }
    int pid = getpid();
    struct procent * prptr = &proctab[pid];
    kprintf("'IO BOUND' PID: %d msclkcounter2: %d cpuusage: %d response time: %d prio: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid), prptr->prprio);
}