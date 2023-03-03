/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    kprintf("Starting tests...\n");
    //test_3_1();
	//test_3_2();
	//test_3_3();

	test_4_2();

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

	// int children2 = xchildrennum(3);
	// kprintf("\nReturned %d CHILDREN to MAIN\n", children2);

	create((void*) sndA, 15, "TESTING Lab 2 4.1", 0, NULL);
	create((void*) sndA, 15, "TESTING Lab 2 4.1", 0, NULL);
	create((void*) sndA, 15, "TESTING Lab 2 4.1", 0, NULL);

	int children = childrennum(3);
	kprintf("Childrennum children: %d\n", children); 

	int children3 = xchildrennum(3);
	kprintf("\nReturned %d CHILDREN to MAIN\n", children3); 


}