/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
clkdisp:
		movl	$1, debugging_var
		cmpl	$0, callback_glbl # determine whether we need to handle a callback function
		je		no_callback
		cmpl	$0, callback_glbl
		jne		execute_callback

no_callback:
		movl	$2, debugging_var
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		sti			# Restore interrupt status
		popal			# Restore registers
		iret			# Return from interrupt

execute_callback:
		movl	$3, debugging_var
		movl	%ebp, helper_global
	    movl	%esp, %ebp # save location of original ESP
		subl	$4, %esp   # move ESP down by 4
		pushal			   # Save registers

		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		# move down EIP, CS, and EFLAGS by 4 bytes
		# EIP is currently located where EBP is
		movl	(%ebp), %eax  # put value at EBP (EIP) in EAX
		movl	%eax, -4(%ebp) # put value in EAX (EIP) 4 bytes lower than EBP address
		movl	4(%ebp), %eax # put value 4 bytes above EBP (CS) into EAX
		movl	%eax, (%ebp)  # put value in EAX (CS) in address of EBP
		movl	8(%ebp), %eax # put value 8 bytes above EBP (EFLAGS) into EAX
		movl	%eax, 4(%ebp)  # put value in EAX (EFLAGS) into address 4 bytes above EBP

		# move EIP back to the top 
		movl 	-4(%ebp), %eax  # put value at 4 bytes below EBP (EIP) into EAX
		movl	%eax, 8(%ebp) # put value in EAX (EIP) into 8 bytes above EBP 

		# at this point, the stack should be ordered: EIP, EFLAGS, CS, SPACE, GEN REGS
		# put CBF into the space
		movl	callback_glbl, %eax
		movl	%eax, -4(%ebp)
		movl	helper_global, %ebp

		sti			# Restore interrupt status
		popal			# Restore registers
		
		movl	$0, callback_glbl
		iret			# Return from interrupt
