#include <xinu.h>

/* lab 2 part 3.1 modifies intr.S to call divzero1()
divzero1() prints an error message and calls kill() */

void divzero1() {
    kprintf("Seems like you tried to divide by 0. This is not allowed.\n");
    kill(getpid());
}