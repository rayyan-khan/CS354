#include <xinu.h>

syscall xchprio(pid32 pid, pri16 newprio) {

    int32 prk_stack_glbl = &proctab[getpid()].prkstack;
    int32 pru_stack_glbl = &proctab[getpid()].prustack;

    pri16 oldprio; 

    asm("movl %3, %%eax\n\t"
        "movl %1, %%ecx\n\t"
        "movl %2, %%ebx\n\t"
        "int $46\n\t"
        "movl %%eax, %0\n\t"
        :"=m"(oldprio)
        :"r"(pid), "g"(newprio), "r"(SYSCHPR)
        :"%eax", "%ebx", "%ecx");

    return oldprio;
}