/* cpubnd.c - cpubnd */

/* new file for lab 3 4.4 */
#include <xinu.h>

void cpubnd(void) {
    while(msclkcounter2 <= STOPPINGTIME) {

    }
    int pid = getpid();
    struct procent * prptr = &proctab[pid];
    kprintf("'CPU BOUND' PID: %d msclkcounter2: %d cpuusage: %d response time: %d prio: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid), prptr->prprio);
}