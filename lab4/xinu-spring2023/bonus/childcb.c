/* childcb.c - childcb */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  childcb - functions as the callback function
 *------------------------------------------------------------------------
 */

void childcb() {
    kprintf("IN BONUS CALLBACK\n");
    mynonreentrant();
    kprintf("EXITING BONUS CALLBACK\n");
}