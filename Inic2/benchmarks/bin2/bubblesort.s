	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/bubblesort.c"
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,40,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -40
	addiu	$1, $zero, 10
	sw	$1, 0($sp)
	addiu	$1, $zero, 9
	sw	$1, 4($sp)
	addiu	$1, $zero, 8
	sw	$1, 8($sp)
	addiu	$1, $zero, 7
	sw	$1, 12($sp)
	addiu	$1, $zero, 6
	sw	$1, 16($sp)
	addiu	$1, $zero, 5
	sw	$1, 20($sp)
	addiu	$3, $zero, 0
	addiu	$1, $zero, 1
	addiu	$2, $zero, 2
	addiu	$4, $zero, 3
	addiu	$5, $zero, 4
	sw	$5, 24($sp)
	sw	$4, 28($sp)
	sw	$2, 32($sp)
	sw	$1, 36($sp)
	lw	$4, 0($sp)
	addiu	$2, $sp, 0
	addiu	$5, $zero, 36
$BB0_1:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $4
	beqz	$1, $BB0_3
	nop
	sw	$7, 0($6)
	j	$BB0_4
	sw	$4, 4($6)
$BB0_3:
	move	 $4, $7
$BB0_4:
	addiu	$3, $3, 4
	bne	$3, $5, $BB0_1
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 32
$BB0_6:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_8
	nop
	sw	$7, 0($6)
	j	$BB0_9
	sw	$5, 4($6)
$BB0_8:
	move	 $5, $7
$BB0_9:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_6
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 28
$BB0_11:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_13
	nop
	sw	$7, 0($6)
	j	$BB0_14
	sw	$5, 4($6)
$BB0_13:
	move	 $5, $7
$BB0_14:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_11
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 24
$BB0_16:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_18
	nop
	sw	$7, 0($6)
	j	$BB0_19
	sw	$5, 4($6)
$BB0_18:
	move	 $5, $7
$BB0_19:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_16
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 20
$BB0_21:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_23
	nop
	sw	$7, 0($6)
	j	$BB0_24
	sw	$5, 4($6)
$BB0_23:
	move	 $5, $7
$BB0_24:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_21
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 16
$BB0_26:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_28
	nop
	sw	$7, 0($6)
	j	$BB0_29
	sw	$5, 4($6)
$BB0_28:
	move	 $5, $7
$BB0_29:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_26
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 12
$BB0_31:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_33
	nop
	sw	$7, 0($6)
	j	$BB0_34
	sw	$5, 4($6)
$BB0_33:
	move	 $5, $7
$BB0_34:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_31
	nop
	addiu	$3, $zero, 0
	lw	$5, 0($sp)
	addiu	$4, $zero, 8
$BB0_36:
	addu	$6, $2, $3
	lw	$7, 4($6)
	sltu	$1, $7, $5
	beqz	$1, $BB0_38
	nop
	sw	$7, 0($6)
	j	$BB0_39
	sw	$5, 4($6)
$BB0_38:
	move	 $5, $7
$BB0_39:
	addiu	$3, $3, 4
	bne	$3, $4, $BB0_36
	nop
	addiu	$3, $zero, -4
	lw	$4, 0($sp)
$BB0_41:
	addu	$5, $2, $3
	lw	$6, 8($5)
	sltu	$1, $6, $4
	beqz	$1, $BB0_43
	nop
	sw	$6, 4($5)
	j	$BB0_44
	sw	$4, 8($5)
$BB0_43:
	move	 $4, $6
$BB0_44:
	addiu	$3, $3, 4
	bnez	$3, $BB0_41
	nop
	addiu	$2, $zero, 0
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end0:
	.size	main, ($func_end0)-main

	.globl	bubble_sort
	.align	2
	.type	bubble_sort,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	bubble_sort
bubble_sort:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	slti	$1, $5, 2
	bnez	$1, $BB1_9
	nop
	addiu	$2, $4, 4
	addiu	$3, $5, -1
	addiu	$5, $zero, 0
	move	 $6, $3
$BB1_2:
	subu	$1, $3, $5
	blez	$1, $BB1_8
	nop
	lw	$8, 0($4)
	addiu	$7, $zero, 0
	move	 $9, $2
$BB1_4:
	lw	$10, 0($9)
	sltu	$1, $10, $8
	beqz	$1, $BB1_6
	addiu	$7, $7, 1
	sw	$10, -4($9)
	j	$BB1_7
	sw	$8, 0($9)
$BB1_6:
	move	 $8, $10
$BB1_7:
	bne	$6, $7, $BB1_4
	addiu	$9, $9, 4
$BB1_8:
	addiu	$5, $5, 1
	bne	$5, $3, $BB1_2
	addiu	$6, $6, -1
$BB1_9:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	bubble_sort
$func_end1:
	.size	bubble_sort, ($func_end1)-bubble_sort


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
