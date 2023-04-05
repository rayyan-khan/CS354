/*  main.c  - main */

#include <xinu.h>

void child_0(void);
void child_1(void);
void parent_0(void);
void parent_1(void);

process	main(void)
{
	/* Run the Xinu shell */

	/* tests */
	pid32 parent_pid;
    parent_pid = create(parent_0, 1024, 20, "Parent process", 0);
    //parent_pid = create(parent_1, 1024, 20, "Parent process", 0);
    resume(parent_pid);

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
        kprintf("\nError occurred in blocking mode of xchildwait\n");
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