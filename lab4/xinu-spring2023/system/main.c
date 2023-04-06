/*  main.c  - main */

#include <xinu.h>

void child_0(void);
void child_1(void);
void parent_0(void);
void parent_1(void);
void childcb(void);
void do_nothing(void);
extern int * debugging_var;
extern void * callback_glbl;

pid32 z;

process	main(void)
{
	/* Run the Xinu shell */

	// /* tests */
	// pid32 parent_pid;
    // // parent_pid = create(parent_0, 1024, 20, "Parent process", 0);
    // parent_pid = create(parent_1, 1024, 20, "Parent process", 0);
    // resume(parent_pid);

    // App initialization.
    if (cbchildregister(&childcb) == SYSERR) {
       kprintf("Callback function registration failed.\n");
       exit();
    }

    // Spawn child process and remember child PID in global variable z.
    z = create(do_nothing, 1024, 20, "child", 0, NULL);
    resume(z);

    #ifdef  XINUDEBUG
    if(debugging_var == 1) {
        kprintf("\n1: Did not exit clkdisp\n");
    }
    else if(debugging_var == 2) {
        kprintf("\n2: Entered no_callback\n");
    }
    else if(debugging_var == 3) {
        kprintf("\n3?: Entered callback\n");
    }
    else if(debugging_var == NULL) {
        kprintf("\null: ndebugging_var is null");
    }
    else {
        kprintf("\ndebugging_var value: %d", debugging_var);
    }
    #endif

    // Then perform other tasks: does not call childcb() nor xchildwait().
    // Example: infinite loop.
    // while(1);

    return OK;
}

void childcb() {
   int x;
   #ifdef XINUDEBUG
   kprintf("GetPID: %d\n", getpid());
   #endif
   x = xchildwait(1, z);
   kprintf("Child process %d has terminated.\n", x);
}

void do_nothing(void) {
    int k;
    int i = 0;
    for(k = 0; k < 15; k++) {
        i++;
    }
    #ifdef XINUDEBUG
    kprintf("in do_nothing\n");
    #endif
}
