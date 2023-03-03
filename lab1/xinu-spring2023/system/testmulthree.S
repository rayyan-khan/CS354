/* Simple code to add two integers passed to addtwo() coded
	in AT&T assembly. Assumes caller follows CDECL. for lab 1 part 5.2 */

        .text
        .globl testmulthree

testmulthree:
        pushl   %ebp
        movl    %esp,%ebp
        pushfl
        pushl   %ebx

        movl    8(%ebp),%ebx
        movl    12(%ebp),%ecx
        movl    16(%ebp),%edx 
        pushl   %ebx
        pushl   %ecx
        pushl   %edx

        call    multhree

        popl    %ebx

        add     $16, %esp
        movl    (%esp),%ebp
        add     $4,%esp
        ret