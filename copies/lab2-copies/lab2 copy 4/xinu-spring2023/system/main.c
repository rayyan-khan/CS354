/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    kprintf("Starting tests...\n");
    //test_3_1();
	//test_3_2();
	//test_3_3();
	//test_4_2();

	test_4_3();

	/* Run the Xinu shell */

	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
    
}

void test_3_1() { // lab 2 3.1
	kprintf("Dividing 3/0: ");
	kprintf("%d\n", 3/0);
}

void test_3_2() { // lab 2 3.2 
	int i;
	for(i=0; i <= 1; i++) {
		kprintf("%d / 0: %d\n", i, i/0);
	}
}

void test_3_3() { // lab 2 3.3 
	int i;
	for(i=0; i <= 10; i++) {
		asm("int $0");
	}
}

void test_4_2() { 
	test_xchildrennum();
}

void test_4_3() {
	
	test_xchildrennum();
	test_xchprio();
	test_xsleepms();
	// test_xkill();
}

void test_xchildrennum() {
	kprintf("\n----Childrennum Tests----\n");
	create((void*) sndA, 15, "TESTING Lab 2 4.3", 0, NULL);
	create((void*) sndA, 15, "TESTING Lab 2 4.3", 0, NULL);
	create((void*) sndA, 15, "TESTING Lab 2 4.3", 0, NULL);

	int children = childrennum(3);
	int children3 = xchildrennum(3);
	kprintf("\nReturned %d children from xchildrennum. %d expected.\n", children3, children);

	kprintf("\n----Childrennum Tests----\n"); 
}

void test_xchprio() {
	kprintf("\n----Change Priority Tests----\n");
	/* 
		Change priority to 4 so we know what the oldPrio will be 
		oldPrio is the return value of xchprio() and chprio()
	*/
	xchprio(getpid(), 4);
	int testChprio1 = xchprio(getpid(), 5);
	kprintf("1:Expected 4 - Actual %d\n", testChprio1);

	int testChprio2 = xchprio(getpid(), 6);
	kprintf("2:Expected 5 - Actual %d\n", testChprio2);

	int testChprio3 = xchprio(getpid(), 7);
	kprintf("3:Expected 6 - Actual %d\n", testChprio3);

	int testChprio4 = xchprio(getpid(), 8);
	kprintf("4:Expected 7 - Actual %d\n", testChprio4);

	kprintf("\n----Change Priority Tests----\n");
}

void test_xsleepms() {
	kprintf("\n\n----Sleepms Test----\n");
	int32 ret = xsleepms(5000);
	kprintf("Output: %d", ret);
	kprintf("\n----Sleepms Test----\n");
}

void test_xkill() {
	kprintf("\n\n----xKill Test----\n");
	int32 ret = xkill(3);
	kprintf("Output: %d", ret);
	kprintf("\n----xKill Test----\n");
}