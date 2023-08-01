/* xdetour.s - xdetour (x86) */

/*------------------------------------------------------------------------
 * xdetour  -  Interrupt dispatcher for clock interrupts (x86 version)
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	xdetour		# Clock interrupt dispatcher
xdetour:
		cli			# Disable further interrupts

		cmpl	$1, use_callback
		je		use_callback_branch
		cmpl	$1,	use_wallx
		je	 	use_wallx_branch

use_callback_branch:
		call	*callback_glbl	# Call high level handler
		movl	$0, callback_glbl		# reset callback_glbl to 0

		cmpl	$1, use_wallx
		je		use_wallx_branch
		jmp		end_branch

use_wallx_branch:
		call	*wallx_glbl
		movl	$0, wallx_glbl
		jmp		end_branch

end_branch:
		sti			# Restore interrupt status
		ret			# Return from interrupt
