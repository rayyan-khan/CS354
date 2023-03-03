#include <xinu.h>

/* lab 2 part 3.1 modifies intr.S to call divzero1()
divzero1() prints an error message and calls kill() */

static int count = 0;

void divzero2() {
    kprintf("Seems like you tried to divide by 0. This is not allowed.\n");

    count++;
    // kprintf("Count: %d\n", count); // debugging
    if(count > 10) {
        // kprintf("Called more than 10 times. Time to kill.\n"); // debugging
        kill(getpid());
    }
}