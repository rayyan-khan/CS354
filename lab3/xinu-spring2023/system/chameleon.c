/* chameleon.c - chameleon */

/* new file for lab 3 4.4 */
#include <xinu.h>

void chameleon(void) {
    while(msclkcounter2 <= STOPPINGTIME) {
        sleepms(0);
    }
    int pid = getpid();
    kprintf("'CMLN' PID: %d MSCTR: %d CU: %d RT: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid));
}