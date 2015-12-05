	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/heapsort.c"
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,104,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -104
	sw	$ra, 100($sp)
	lui	$1, %hi(gen_random.last)
	lw	$6, %lo(gen_random.last)($1)
	addiu	$5, $zero, 4
	lui	$1, 7671
	ori	$3, $1, 22145
	addiu	$2, $sp, 16
	addiu	$4, $zero, 84
$BB0_1:
	sll	$1, $6, 2
	addu	$1, $1, $6
	sll	$7, $6, 5
	addu	$1, $7, $1
	sll	$7, $6, 8
	subu	$1, $7, $1
	sll	$6, $6, 12
	subu	$1, $6, $1
	addiu	$1, $1, 29573
	multu	$1, $3
	mfhi	$6
	addiu	$7, $5, 4
	addu	$5, $2, $5
	srl	$6, $6, 14
	sll	$8, $6, 6
	sll	$9, $6, 7
	addu	$8, $9, $8
	sll	$9, $6, 9
	addu	$8, $9, $8
	sll	$9, $6, 13
	addu	$8, $9, $8
	sll	$6, $6, 17
	addu	$6, $6, $8
	subu	$6, $1, $6
	sw	$6, 0($5)
	bne	$7, $4, $BB0_1
	move	 $5, $7
	lui	$1, %hi(gen_random.last)
	sw	$6, %lo(gen_random.last)($1)
	addiu	$3, $zero, 11
	addiu	$4, $zero, 20
	j	$BB0_4
	addiu	$5, $zero, 1
$BB0_3:
	sll	$1, $9, 2
	addu	$1, $2, $1
	sw	$6, 0($1)
$BB0_4:
	slti	$1, $3, 2
	bnez	$1, $BB0_6
	nop
	addiu	$3, $3, -1
	sll	$1, $3, 2
	addu	$1, $2, $1
	lw	$6, 0($1)
	j	$BB0_7
	nop
$BB0_6:
	sll	$1, $4, 2
	addu	$1, $2, $1
	lw	$6, 0($1)
	lw	$7, 20($sp)
	addiu	$4, $4, -1
	beq	$4, $5, $BB0_15
	sw	$7, 0($1)
$BB0_7:
	sll	$8, $3, 1
	slt	$1, $4, $8
	move	 $7, $3
	bnez	$1, $BB0_3
	move	 $9, $3
$BB0_8:
	slt	$1, $8, $4
	beqz	$1, $BB0_10
	nop
	sll	$1, $8, 2
	addu	$1, $2, $1
	lw	$1, 0($1)
	ori	$9, $8, 1
	sll	$10, $9, 2
	addu	$10, $2, $10
	lw	$10, 0($10)
	sltu	$1, $1, $10
	movn	$8, $9, $1
	j	$BB0_11
	move	 $9, $8
$BB0_10:
	move	 $9, $8
$BB0_11:
	sll	$1, $9, 2
	addu	$1, $2, $1
	lw	$8, 0($1)
	sltu	$1, $6, $8
	beqz	$1, $BB0_14
	nop
	sll	$1, $7, 2
	addu	$1, $2, $1
	sw	$8, 0($1)
	sll	$8, $9, 1
	slt	$1, $4, $8
	beqz	$1, $BB0_8
	move	 $7, $9
	j	$BB0_3
	nop
$BB0_14:
	j	$BB0_3
	move	 $9, $7
$BB0_15:
	sw	$6, 20($sp)
	lw	$4, 96($sp)
	jal	printnum
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
	addiu	$2, $zero, 0
	lw	$ra, 100($sp)
	jr	$ra
	addiu	$sp, $sp, 104
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main

	.globl	heapsort
	.align	2
	.type	heapsort,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	heapsort
heapsort:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	sra	$1, $4, 1
	addiu	$2, $1, 1
	j	$BB1_2
	addiu	$3, $zero, 1
$BB1_1:
	sll	$1, $9, 2
	addu	$1, $5, $1
	sw	$6, 0($1)
$BB1_2:
	slti	$1, $2, 2
	bnez	$1, $BB1_4
	nop
	addiu	$2, $2, -1
	sll	$1, $2, 2
	addu	$1, $5, $1
	lw	$6, 0($1)
	j	$BB1_5
	nop
$BB1_4:
	sll	$1, $4, 2
	addu	$1, $5, $1
	lw	$6, 0($1)
	lw	$7, 4($5)
	addiu	$4, $4, -1
	beq	$4, $3, $BB1_13
	sw	$7, 0($1)
$BB1_5:
	sll	$8, $2, 1
	slt	$1, $4, $8
	move	 $7, $2
	bnez	$1, $BB1_1
	move	 $9, $2
$BB1_6:
	slt	$1, $8, $4
	beqz	$1, $BB1_8
	nop
	sll	$1, $8, 2
	addu	$1, $5, $1
	lw	$1, 0($1)
	ori	$9, $8, 1
	sll	$10, $9, 2
	addu	$10, $5, $10
	lw	$10, 0($10)
	sltu	$1, $1, $10
	movn	$8, $9, $1
	j	$BB1_9
	move	 $9, $8
$BB1_8:
	move	 $9, $8
$BB1_9:
	sll	$1, $9, 2
	addu	$1, $5, $1
	lw	$8, 0($1)
	sltu	$1, $6, $8
	beqz	$1, $BB1_12
	nop
	sll	$1, $7, 2
	addu	$1, $5, $1
	sw	$8, 0($1)
	sll	$8, $9, 1
	slt	$1, $4, $8
	beqz	$1, $BB1_6
	move	 $7, $9
	j	$BB1_1
	nop
$BB1_12:
	j	$BB1_1
	move	 $9, $7
$BB1_13:
	jr	$ra
	sw	$6, 4($5)
	.set	at
	.set	macro
	.set	reorder
	.end	heapsort
$func_end1:
	.size	heapsort, ($func_end1)-heapsort

	.globl	gen_random
	.align	2
	.type	gen_random,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	gen_random
gen_random:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$1, %hi(gen_random.last)
	lw	$2, %lo(gen_random.last)($1)
	sll	$3, $2, 2
	addu	$3, $3, $2
	sll	$4, $2, 5
	addu	$3, $4, $3
	sll	$4, $2, 8
	lui	$5, 7671
	subu	$3, $4, $3
	ori	$4, $5, 22145
	sll	$2, $2, 12
	subu	$2, $2, $3
	addiu	$2, $2, 29573
	multu	$2, $4
	mfhi	$3
	srl	$3, $3, 14
	sll	$4, $3, 6
	sll	$5, $3, 7
	addu	$4, $5, $4
	sll	$5, $3, 9
	addu	$4, $5, $4
	sll	$5, $3, 13
	addu	$4, $5, $4
	sll	$3, $3, 17
	addu	$3, $3, $4
	subu	$2, $2, $3
	jr	$ra
	sw	$2, %lo(gen_random.last)($1)
	.set	at
	.set	macro
	.set	reorder
	.end	gen_random
$func_end2:
	.size	gen_random, ($func_end2)-gen_random

	.type	$.str,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
$.str:
	.asciz	"\n"
	.size	$.str, 2

	.type	gen_random.last,@object
	.data
	.align	2
gen_random.last:
	.4byte	42
	.size	gen_random.last, 4


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
