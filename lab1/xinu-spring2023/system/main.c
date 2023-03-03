/*  main.c  - main */

#include <xinu.h>
#include <clock.h>

process	main(void)
{
	/* Run the Xinu shell */
	pid32 proc = getpid();
	kprintf("\n Executing main() by test process: %d", proc);
	recvclr();

	//test_3_1_d();
	//test_3_2_b();
	//test_4_1();
	//test_4_2();
	//test_5_1();
	//test_5_2();

	resume(createmod(shell, 23, 8192, 50, "shell1", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(createmod(shell, 23, 4096, 20, "shell2", 1, CONSOLE));
	}
	return OK;
    
}

void test_3_1_d () {
	kprintf("\nSection 3.1d\n");
	int proc1 = createmod((void*) sndA, 25, 15, "TESTING 3.1D", 0, NULL);
	int proc2 = createmod((void*) sndA, 24, 15, "TESTING 3.1D", 0, NULL);
	int proc3 = createmod((void*) sndA, 26, 15, "TESTING 3.1D", 0, NULL);
	int proc4 = createmod((void*) sndA, 27, 15, "TESTING 3.1D", 0, NULL);
	int children = childrennum(3);
	kprintf("\nChildrennum: %d (Expected: 4)\n", children);
}	

void test_3_2_b () {
	kprintf("Section 3.2:\n");
	resume( create(sndA, 1024, 20, "process1", 0));
	resume( create(sndB, 1024, 20, "process2", 0));
}

void test_4_1 () {
	/* test lab 1 4.1 */
	kprintf("\nSection 4.1\n");
	kprintf("\nmsclkcounter1: %d\n msclkcounter2: %d\n", msclkcounter1, msclkcounter2);
	sleep(5);
	kprintf("\nmsclkcounter1: %d\n msclkcounter2: %d\n", msclkcounter1, msclkcounter2);
}

void test_4_2 () {
	kprintf("\nSection 4.2:\n");
	test_3_2_b();
}

void test_5_1 () {
	kprintf("\nSection 5.1:\n");
	kprintf("Section 5.1 addtwo: %d (Expected: 8)\n", addtwo(5, 3));
	kprintf("Section 5.2 mintwo: %d (Expected: 3)\n", mintwo(5, 3));
	kprintf("Section 5.2 mintwo: %d (Expected: 1)\n", mintwo(1, 9));
	kprintf("Section 5.2 mintwo: %d (Expected: -3)\n", mintwo(-3, 3));
}

void test_5_2 () {
	kprintf("\nSection 5.2:\n");
	kprintf("Section 5.2 testmulthree: %d (Expected: 6)\n", testmulthree(1, 2, 3));
	kprintf("Section 5.2 testmulthree: %d (Expected: 0)\n", testmulthree(0, 1, 2));
	kprintf("Section 5.2 testmulthree: %d (Expected: 24)\n", testmulthree(3, 4, 2));
	kprintf("Section 5.2 testmulthree: %d (Expected: 6)\n", testmulthree(1, 2, 3));
	return;
}