/* Simple code to add two integers passed to addtwo() coded
	in AT&T assembly. Assumes caller follows CDECL. for lab 1 part 5.1 */

        .text
        .globl mintwo

mintwo:
        pushl   %ebp
        movl    %esp,%ebp
        pushfl
        pushl   %ebx
        movl    8(%ebp),%eax
        movl    12(%ebp),%ebx
        # compare ebx to eax
        cmpl    %ebx,%eax
        jg      branch
        popl    %ebx
        popfl
        movl    (%esp),%ebp
        add     $4,%esp
        ret

branch:
    movl    %ebx,%eax
    popl    %ebx
    popfl
    movl    (%esp),%ebp
    add     $4,%esp
    ret
