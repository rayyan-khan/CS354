#include <xinu.h>

syscall xchildrennum(pid32 pid) {
    
    kprintf("IN XCHILDRENNUM\n");
    uint32 numchildren=1;

    asm("movl %2, %%eax\n\t"
        "movl %1, %%ebx\n\t"
        "int $46\n\t"
        "movl %%eax, %0\n\t"
        :"=r"(numchildren)
        :"r"(pid), "r"(10)
        :"%eax", "%ebx");

    kprintf("FINISHED ASM\n");
    kprintf("numchildren: %d", numchildren);
    return numchildren;
}