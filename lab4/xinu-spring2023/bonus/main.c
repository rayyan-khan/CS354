/*  main.c  - main */

#include <xinu.h>

void childcb(void);
void do_nothing(void);

pid32 z;

process	main(void)
{
	/* Run the Xinu shell */

	/* tests */
    // App initialization.
    if (cbchildregister(&childcb) == SYSERR) {
       kprintf("Callback function registration failed.\n");
       exit();
    }

    // Spawn child process and remember child PID in global variable z.
    z = create(do_nothing, 1024, 20, "child", 0, NULL);
    resume(z);
    mynonreentrant();

    // Then perform other tasks: does not call childcb() nor xchildwait().
    // Example: infinite loop.
    while(1);

    return OK;
}

// void childcb() {
//    int x;
//    #ifdef XINUDEBUG
//    kprintf("GetPID: %d\n", getpid());
//    #endif
//    x = xchildwait(1, z);
//    kprintf("Child process %d has terminated.\n", x);
// }

// void childcb() {
//     kprintf("IN BONUS CALLBACK\n");
//     mynonreentrant();
//     kprintf("EXITING BONUS CALLBACK\n");
// }

void do_nothing(void) {
    int k;
    int i = 0;
    for(k = 0; k < 100; k++) {
        i++;
    }
    #ifdef XINUDEBUG
    kprintf("in do_nothing\n");
    #endif
}