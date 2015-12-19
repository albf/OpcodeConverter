	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/loop.c"
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$fp,24,$ra
	.mask 	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$fp, 20($sp)
	move	 $fp, $sp
	sw	$zero, 16($fp)
	sw	$4, 12($fp)
	sw	$5, 8($fp)
	sw	$zero, 0($fp)
	sw	$zero, 4($fp)
$BB0_1:
	lw	$1, 4($fp)
	slti	$1, $1, 10000
	beqz	$1, $BB0_5
	nop
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$1, 0($fp)
	lw	$2, 0($fp)
	lw	$3, 4($fp)
	lw	$4, 0($fp)
	lw	$5, 4($fp)
	lw	$6, 0($fp)
	lw	$2, 4($fp)
	lw	$3, 0($fp)
	lw	$4, 4($fp)
	lw	$5, 0($fp)
	lw	$6, 4($fp)
	addiu	$1, $1, 5
	sw	$1, 0($fp)
	lw	$1, 4($fp)
	addiu	$1, $1, 1
	sw	$1, 4($fp)
	j	$BB0_1
	nop
$BB0_5:
	lw	$2, 0($fp)
	move	 $sp, $fp
	lw	$fp, 20($sp)
	addiu	$sp, $sp, 24
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
