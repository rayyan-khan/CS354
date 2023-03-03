#include <xinu.h>

syscall xsleepms(int32 delay) {

    int32 prk_stack_glbl = &proctab[getpid()].prkstack;
    int32 pru_stack_glbl = &proctab[getpid()].prustack;

    int32 ret = 0;

    kprintf("");

    asm("movl %2, %%eax\n\t"
        "movl %1, %%ebx\n\t"
        "int $46\n\t"
        "movl %%eax, %0\n\t"
        :"=r"(ret)
        :"r"(delay), "r"(SYSSLP)
        :"%eax", "%ebx");

    return ret;
}