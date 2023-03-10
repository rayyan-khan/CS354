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
    kprintf("'IO' PID: %d MSCTR: %d CU: %d RT: %d PRIO: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid), prptr->prprio);
}