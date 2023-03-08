/*  main.c  - main */

#include <xinu.h>

void test_3_1(void);

process	main(void)
{

	/* lab 3 test */
	test_3_1();

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

void test_3_1() {
	int i = 0;
	int j = 0;

	for(i = 0; i < 5000000; i++) {
		j++;
	}

	kprintf("\n3.1 cpuusage result: %d\n", cpuusage(getpid()));
}