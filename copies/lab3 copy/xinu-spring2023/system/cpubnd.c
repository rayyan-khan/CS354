/* cpubnd.c - cpubnd */

/* new file for lab 3 4.4 */
#include <xinu.h>

void cpubnd(void) {
    while(msclkcounter2 <= STOPPINGTIME) {

    }
    int pid = getpid();
    struct procent * prptr = &proctab[pid];
    kprintf("'CPU' PID: %d MSCTR: %d CU: %d RT: %d PRIO: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid), prptr->prprio);
}