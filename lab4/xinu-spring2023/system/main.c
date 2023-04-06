/*  main.c  - main */

#include <xinu.h>

void child_0(void);
void child_1(void);
void parent_0(void);
void parent_1(void);
void childcb(void);
void do_nothing(void);
int32 debugging_var;
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

    if(debugging_var == 1) {
        kprintf("\n1: Did not exit clkdisp\n");
    }
    else if(debugging_var == 2) {
        kprintf("\n2: Entered no_callback\n");
    }
    else if(debugging_var == 3) {
        kprintf("\n3: Entered callback\n");
    }
    else if(debugging_var == NULL) {
        kprintf("\null: ndebugging_var is null");
    }
    else {
        kprintf("\ndebugging_var value: %d", debugging_var);
    }

    // Then perform other tasks: does not call childcb() nor xchildwait().
    // Example: infinite loop.
    // while(1);

    return OK;
    
}

void child_0(void) {
    kprintf("\nChild process with PID %d started\n", getpid());
    sleepms(5000);
    kprintf("\nChild process with PID %d finished\n", getpid());
    sleepms(100);
}

void child_1(void) {
    kprintf("\nChild process with PID %d started\n", getpid());
    int i;

    for(i = 0; i < 100000; i++){

    }
    kprintf("\nChild process with PID %d finished with i=%d", getpid(), i);
}

void parent_0(void) {

    pid32 child_pid;
    pid32 result;

    // Create a child process
    child_pid = create((void *)child_0, 1024, 20, "Child process", 0);

    // Check if the child process was created successfully
    if (child_pid == SYSERR) {
        kprintf("\nFailed to create the child process\n");
    }

    // Start the child process
    //resume(child_pid);

    // Test the blocking mode of xchildwait
    kprintf("\nParent process waiting for child process (blocking mode)...\n");
    result = xchildwait(0, child_pid);
    if (result != SYSERR) {
        kprintf("\nParent process unblocked. Child process with PID %d terminated.\n", result);
    } else {
        kprintf("\nError occurred in blocking mode of xchildwait: result is %d\n", result);
    }

    kprintf("\nParent process is back\n");

}

void parent_1(void){

    pid32 child_pid;
    int32 result;

    kprintf("\nParent process (PID: %d) started.\n", getpid());

    // Create a child process
    child_pid = create(child_1, 1024, 19, "Child Process", 0);
    kprintf("\n PID OF CHILD: %d\n", child_pid);

    if (child_pid == SYSERR) {
        kprintf("\nError: Failed to create child process.\n");
    }

    // Resume the child process
    resume(child_pid);

    // Call xchildwait() with non-blocking mode (1) before the child process completes
    result = xchildwait(1, child_pid);
    if (result == SYSERR) {
        kprintf("\nChild process (1PID: %d) has not completed yet.\n", child_pid);
    } else {
        kprintf("\nChild process (1PID: %d) has completed.\n", result);
    }

    sleepms(4000);

    // Call xchildwait() with non-blocking mode (1) after the child process completes
    result = xchildwait(1, child_pid);
    if (result == SYSERR) {
        kprintf("\nChild process (2PID: %d) has not completed yet.\n", child_pid);
    } else {
        kprintf("\nChild process (2PID: %d) has completed.\n", result);
    }

    kprintf("\nParent process (PID: %d) completed.\n", getpid()); 

}

void childcb() {
   int x;
   x = xchildwait(1, z);
   kprintf("Child process %d has terminated.\n", x);
}

void do_nothing(void) {
    int k;
    int i = 0;
    for(k = 0; k < 10; k++) {
        i++;
    }
    kprintf("in do_nothing\n");
}
