#include <xinu.h>

syscall xkill(pid32 pid) {
    
    uint32 ret = 0;

    int32 prk_stack_glbl = &proctab[getpid()].prkstack;
    int32 pru_stack_glbl = &proctab[getpid()].prustack;

    asm("movl %2, %%eax\n\t"
        "movl %1, %%ebx\n\t"
        "int $46\n\t"
        "movl %%eax, %0\n\t"
        :"=r"(ret)
        :"r"(pid), "r"(SYSKILL)
        :"%eax", "%ebx");

    // kprintf("FINISHED ASM\n"); // debugging
    // kprintf("numchildren: %d", numchildren); // debugging
    return ret;
}