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
		movl	%esp, esp_global

		addl	$4, %esp
		pushal	# save registers

		movl	(esp_global), %eax # move EIP value into eip_global
		movl	%eax, eip_global

		# move down CS and EFLAGS
		movl	(%esp), %eax # put CS in EAX
		movl	%eax, (%esp) # put CS at address of ESP (where EIP used to be)
		movl	8(%esp), %eax  # put EFLAGS in EAX
		movl	%eax, 4(%esp)  # put EFLAGS at address of ESP+4

		# put EIP above EFLAGS
		movl	(eip_global), %eax		# move EIP value into EAX
		movl	%eax, esp_global+8		# move EIP into the address of esp_global+8

		# put CBF below CS
		movl	(callback_glbl), %eax	# move callback value into EAX
		movl	%eax, esp_global-4	# the address to put CBF would be (esp_global - 4) since CS is at ESP

		# Code from original clkdisp
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler

		sti			# Restore interrupt status
		popal			# Restore registers
		movl	$0, callback_glbl	# reset value of callback_glbl
		iret			# Return from interrupt
