/*  main.c  - main */

#include <xinu.h>

void test_3_1(void);
void test_3_2(void);
void test_4_4a(void);
void test_4_4b(void);
void test_4_4c(void);
void test_4_4d(void);

process	main(void)
{
	/* lab 3 test */
	// test_3_1();
	 test_3_2();
	sleepms(0);
	sleepms(0);

	// test_4_4a();
	// test_4_4b();
	// test_4_4c();
	// test_4_4d();
	// starve();

	/* Run the Xinu shell */

	recvclr();
	// sresume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */

	// while (TRUE) {
	// 	receive();
	// 	sleepms(200);
	// 	kprintf("\n\nMain process recreating shell\n\n");
	// 	resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	// }
	return OK;
    
}

void test_3_1() {
	int i = 0;

	for(i = 0; i < 5000000; i++) {
	}

	kprintf("\n3.1 cpuusage result: %d\n", cpuusage(getpid()));
}

void test_3_2() {
	// print main process response time, see if its the same as msclkcounter
	// use sleep() to put things back in the readylist

	kprintf("msclkcounter2: %d response time initial: %d\n", msclkcounter2, responsetime(getpid()));

	struct procent * prptr = &proctab[getpid()];
	
	kprintf("1: prctxswcount: %d prresptime: %d\n", prptr->prctxswcount, prptr->prresptime);
	int k;
	for(k = 0; k < 10000; k++) {
		sleepms(1);
	}
	kprintf("2: prctxswcount: %d prresptime: %d\n", prptr->prctxswcount, prptr->prresptime);
	kprintf("msclkcounter2: %d response time main: %d\n", msclkcounter2, responsetime(getpid()));
}

void test_4_4a() {

	kprintf("\n**********BENCHMARK A**********************\n");
	pid32 pid1 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid2 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid3 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid4 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid5 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid6 = create(cpubnd, 1024, 5, "test 4.4 a", 0);

	resume(pid1);
	resume(pid2);
	resume(pid3);
	resume(pid4);
	resume(pid5);
	resume(pid6);
}

void test_4_4b(void) {
	kprintf("\n**********BENCHMARK B**********************\n");
	pid32 pid1 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid2 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid3 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid4 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid5 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid6 = create(iobnd, 1024, 5, "test 4.4 a", 0);

	resume(pid1);
	resume(pid2);
	resume(pid3);
	resume(pid4);
	resume(pid5);
	resume(pid6);
}

void test_4_4c(void) {
	kprintf("\n**********BENCHMARK C**********************\n");
	pid32 pid1 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid2 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid3 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid4 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid5 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid6 = create(cpubnd, 1024, 5, "test 4.4 a", 0);

	resume(pid1);
	resume(pid2);
	resume(pid3);
	resume(pid4);
	resume(pid5);
	resume(pid6);
}

void test_4_4d(void) {
	kprintf("\n**********BENCHMARK D**********************\n");
	pid32 pid5 = create(chameleon, 1024, 5, "test 4.4 a", 0);
	pid32 pid1 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid2 = create(cpubnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid3 = create(iobnd, 1024, 5, "test 4.4 a", 0);
	pid32 pid4 = create(iobnd, 1024, 5, "test 4.4 a", 0);

	resume(pid5);
	resume(pid1);
	resume(pid2);
	resume(pid3);
	resume(pid4);
}

void starve(void) {
	kprintf("\n*******************BONUS**********************\n");
	pid32 pid1 = create(iobnd9, 1024, 5, "test 4.4 a", 0);
	pid32 pid2 = create(iobnd9, 1024, 5, "test 4.4 a", 0);
	pid32 pid3 = create(iobnd9, 1024, 5, "test 4.4 a", 0);
	pid32 pid4 = create(iobnd9, 1024, 5, "test 4.4 a", 0);
	pid32 pid5 = create(iobnd9, 1024, 5, "test 4.4 a", 0);
	pid32 pid6 = create(cpubnd, 1024, 5, "test 4.4 a", 0);

	resume(pid1);
	resume(pid2);
	resume(pid3);
	resume(pid4);
	resume(pid5);
	resume(pid6);
}