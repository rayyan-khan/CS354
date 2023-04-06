/* clkdisp.s - clkdisp (x86) */

/*------------------------------------------------------------------------
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */

#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
clkdisp:
		cmpl	$0, callback_glbl # determine whether we need to handle a callback function
		je		no_callback
		cmpl	$0, callback_glbl
		jne		execute_callback		

no_callback:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		sti			# Restore interrupt status
		popal			# Restore registers
		iret			# Return from interrupt

execute_callback:
		subl	$4, %esp
		# pushl	%eax
		pushal		# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		movl	36(%esp), %eax			# move EIP into eip_global
		movl	%eax, eip_global		#
		movl	40(%esp), %eax	        # move CS into the spot previously occupied by EIP
		movl	%eax, 36(%esp)			#
		movl	44(%esp), %eax			# move EFLAGS into spot previously occupied by CS
		movl	%eax, 40(%esp)			#
		movl	eip_global, %eax		# move EIP into the spot previously held by EFLAGS before it was moved
		movl	%eax, 44(%esp)			#
		movl	callback_glbl, %eax		# move callback_glbl into the spot below CS
		movl	%eax, 32(%esp)			#
		movl	$0, callback_glbl		# reset callback_glbl

		sti			# Restore interrupt status
		popal			# Restore registers
		iret	
