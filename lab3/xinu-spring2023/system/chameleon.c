/* chameleon.c - chameleon */

/* new file for lab 3 4.4 */
#include <xinu.h>

void chameleon(void) {
    int i;
    int j = 0;
    for(i = 0; i < 5000000; i++) {
        j++;
        sleep(0);
    }
    int pid = getpid();
    kprintf("'Chameleon' PID: %d msclkcounter2: %d cpuusage: %d response time: %d\n", pid, msclkcounter2, cpuusage(pid), responsetime(pid));
}