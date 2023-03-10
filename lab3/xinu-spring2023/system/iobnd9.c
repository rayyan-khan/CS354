/* iobnd9.c - iobnd9 */

/* new file for lab 3 4.4 */
#include <xinu.h>

void iobnd9(void) {
    while(msclkcounter2 <= STOPPINGTIME) {
        int i;
        for (i = 0; i < 5000000; i++) {  
            sleepms(0);
        }  
    }
    int pid = getpid();
    kprintf("'IO9' PID: %d MSCTR: %d CU: %d RT: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid));
}