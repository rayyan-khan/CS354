/* cpubnd.c - cpubnd */

/* new file for lab 3 4.4 */
#include <xinu.h>

void cpubnd(void) {
    while(msclkcounter2 <= STOPPINGTIME) {

    }
    int pid = getpid();
    kprintf("'CPU' PID: %d MSCTR: %d CU: %d RT: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid));

}