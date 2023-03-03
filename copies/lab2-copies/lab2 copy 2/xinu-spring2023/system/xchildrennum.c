#include <xinu.h>

syscall xchildrennum(pid32 pid) {
    
    // kprintf(""); // debugging
    uint32 numchildren=1;

    int32 prk_stack_glbl = &proctab[pid].prkstack;
    int32 pru_stack_glbl = &proctab[pid].prustack;

    asm("movl %2, %%eax\n\t"
        "movl %1, %%ebx\n\t"
        "int $46\n\t"
        "movl %%eax, %0\n\t"
        :"=r"(numchildren)
        :"r"(pid), "r"(10)
        :"%eax", "%ebx");

    // kprintf("FINISHED ASM\n"); // debugging
    // kprintf("numchildren: %d", numchildren); // debugging
    return numchildren;
}