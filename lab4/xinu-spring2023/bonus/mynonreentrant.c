/* mynonreentrant.c - mynonreentrant */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  mynonreentrant - to show that the callback function has a higher priority than main
 *------------------------------------------------------------------------
 */

void mynonreentrant(void) {
    int k;
    for (k = 0; k < 300000; k++) {
        if (k % 10000 == 0) {
            kprintf("k: %d\n", k/10000);
        }
    }
}