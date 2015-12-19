	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/minmax.c"
	.text
	.globl	win
	.align	2
	.type	win,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	win
win:
	.frame	$sp,96,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -96
	sw	$zero, 0($sp)
	addiu	$1, $zero, 1
	sw	$1, 4($sp)
	addiu	$5, $zero, 2
	sw	$5, 8($sp)
	addiu	$6, $zero, 3
	sw	$6, 12($sp)
	addiu	$7, $zero, 4
	sw	$7, 16($sp)
	addiu	$8, $zero, 5
	sw	$8, 20($sp)
	addiu	$2, $sp, 0
	addiu	$3, $2, 12
	addiu	$2, $zero, 0
	addiu	$9, $zero, 8
	addiu	$10, $zero, 7
	addiu	$11, $zero, 6
	sw	$11, 24($sp)
	sw	$10, 28($sp)
	sw	$9, 32($sp)
	sw	$zero, 36($sp)
	sw	$6, 40($sp)
	sw	$11, 44($sp)
	sw	$1, 48($sp)
	sw	$7, 52($sp)
	sw	$10, 56($sp)
	sw	$5, 60($sp)
	sw	$8, 64($sp)
	sw	$9, 68($sp)
	sw	$zero, 72($sp)
	sw	$7, 76($sp)
	sw	$9, 80($sp)
	sw	$5, 84($sp)
	sw	$7, 88($sp)
	sw	$11, 92($sp)
	j	$BB0_2
	addiu	$5, $zero, 0
$BB0_1:
	addiu	$1, $3, 12
	lw	$2, 0($3)
	move	 $3, $1
$BB0_2:
	sll	$1, $2, 2
	addu	$1, $4, $1
	lw	$2, 0($1)
	beqz	$2, $BB0_5
	nop
	lw	$1, -8($3)
	sll	$1, $1, 2
	addu	$1, $4, $1
	lw	$1, 0($1)
	bne	$2, $1, $BB0_5
	nop
	lw	$1, -4($3)
	sll	$1, $1, 2
	addu	$1, $4, $1
	lw	$1, 0($1)
	beq	$2, $1, $BB0_6
	nop
$BB0_5:
	addiu	$5, $5, 1
	slti	$1, $5, 8
	bnez	$1, $BB0_1
	addiu	$2, $zero, 0
$BB0_6:
	jr	$ra
	addiu	$sp, $sp, 96
	.set	at
	.set	macro
	.set	reorder
	.end	win
$func_end0:
	.size	win, ($func_end0)-win

	.globl	minimax
	.align	2
	.type	minimax,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	minimax
minimax:
	.frame	$sp,40,$ra
	.mask 	0x801f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -40
	sw	$ra, 36($sp)
	sw	$20, 32($sp)
	sw	$19, 28($sp)
	sw	$18, 24($sp)
	sw	$17, 20($sp)
	sw	$16, 16($sp)
	move	 $18, $5
	jal	win
	move	 $17, $4
	beqz	$2, $BB1_2
	nop
	j	$BB1_22
	mul	$16, $2, $18
$BB1_2:
	lw	$1, 0($17)
	beqz	$1, $BB1_4
	negu	 $19, $18
	addiu	$16, $zero, -2
	j	$BB1_5
	addiu	$20, $zero, -1
$BB1_4:
	sw	$18, 0($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	sw	$zero, 0($17)
	negu	 $1, $2
	slti	$2, $2, 2
	addiu	$16, $zero, -2
	movn	$16, $1, $2
	addiu	$20, $2, -1
$BB1_5:
	lw	$1, 4($17)
	bnez	$1, $BB1_7
	nop
	sw	$18, 4($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 4($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 1
	movn	$20, $1, $2
$BB1_7:
	lw	$1, 8($17)
	bnez	$1, $BB1_9
	nop
	sw	$18, 8($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 8($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 2
	movn	$20, $1, $2
$BB1_9:
	lw	$1, 12($17)
	bnez	$1, $BB1_11
	nop
	sw	$18, 12($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 12($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 3
	movn	$20, $1, $2
$BB1_11:
	lw	$1, 16($17)
	bnez	$1, $BB1_13
	nop
	sw	$18, 16($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 16($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 4
	movn	$20, $1, $2
$BB1_13:
	lw	$1, 20($17)
	bnez	$1, $BB1_15
	nop
	sw	$18, 20($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 20($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 5
	movn	$20, $1, $2
$BB1_15:
	lw	$1, 24($17)
	bnez	$1, $BB1_17
	nop
	sw	$18, 24($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 24($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 6
	movn	$20, $1, $2
$BB1_17:
	lw	$1, 28($17)
	bnez	$1, $BB1_19
	nop
	sw	$18, 28($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 28($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 7
	movn	$20, $1, $2
$BB1_19:
	lw	$1, 32($17)
	bnez	$1, $BB1_21
	nop
	sw	$18, 32($17)
	move	 $4, $17
	jal	minimax
	move	 $5, $19
	negu	 $1, $2
	sw	$zero, 32($17)
	slt	$2, $16, $1
	movn	$16, $1, $2
	addiu	$1, $zero, 8
	movn	$20, $1, $2
$BB1_21:
	addiu	$1, $zero, -1
	xor	$1, $20, $1
	movz	$16, $zero, $1
$BB1_22:
	move	 $2, $16
	lw	$16, 16($sp)
	lw	$17, 20($sp)
	lw	$18, 24($sp)
	lw	$19, 28($sp)
	lw	$20, 32($sp)
	lw	$ra, 36($sp)
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	minimax
$func_end1:
	.size	minimax, ($func_end1)-minimax

	.globl	computerMove
	.align	2
	.type	computerMove,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	computerMove
computerMove:
	.frame	$sp,40,$ra
	.mask 	0x800f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -40
	sw	$ra, 36($sp)
	sw	$19, 32($sp)
	sw	$18, 28($sp)
	sw	$17, 24($sp)
	sw	$16, 20($sp)
	move	 $16, $4
	lw	$1, 0($16)
	beqz	$1, $BB2_2
	nop
	addiu	$17, $zero, -1
	j	$BB2_3
	addiu	$18, $zero, -2
$BB2_2:
	addiu	$1, $zero, 1
	sw	$1, 0($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	sw	$zero, 0($16)
	negu	 $1, $2
	slti	$2, $2, 2
	addiu	$18, $zero, -2
	movn	$18, $1, $2
	addiu	$17, $2, -1
$BB2_3:
	lw	$1, 4($16)
	bnez	$1, $BB2_5
	nop
	addiu	$19, $zero, 1
	sw	$19, 4($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	sw	$zero, 4($16)
	negu	 $1, $2
	slt	$2, $18, $1
	movn	$18, $1, $2
	movn	$17, $19, $2
$BB2_5:
	lw	$1, 8($16)
	bnez	$1, $BB2_7
	nop
	addiu	$1, $zero, 1
	sw	$1, 8($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 8($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 2
	movn	$17, $1, $2
$BB2_7:
	lw	$1, 12($16)
	bnez	$1, $BB2_9
	nop
	addiu	$1, $zero, 1
	sw	$1, 12($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 12($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 3
	movn	$17, $1, $2
$BB2_9:
	lw	$1, 16($16)
	bnez	$1, $BB2_11
	nop
	addiu	$1, $zero, 1
	sw	$1, 16($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 16($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 4
	movn	$17, $1, $2
$BB2_11:
	lw	$1, 20($16)
	bnez	$1, $BB2_13
	nop
	addiu	$1, $zero, 1
	sw	$1, 20($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 20($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 5
	movn	$17, $1, $2
$BB2_13:
	lw	$1, 24($16)
	bnez	$1, $BB2_15
	nop
	addiu	$1, $zero, 1
	sw	$1, 24($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 24($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 6
	movn	$17, $1, $2
$BB2_15:
	lw	$1, 28($16)
	bnez	$1, $BB2_17
	nop
	addiu	$1, $zero, 1
	sw	$1, 28($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	negu	 $1, $2
	sw	$zero, 28($16)
	slt	$2, $18, $1
	movn	$18, $1, $2
	addiu	$1, $zero, 7
	movn	$17, $1, $2
$BB2_17:
	lw	$1, 32($16)
	bnez	$1, $BB2_19
	nop
	addiu	$1, $zero, 1
	sw	$1, 32($16)
	move	 $4, $16
	jal	minimax
	addiu	$5, $zero, -1
	sw	$zero, 32($16)
	negu	 $1, $2
	slt	$1, $18, $1
	addiu	$2, $zero, 8
	movn	$17, $2, $1
$BB2_19:
	sll	$1, $17, 2
	addu	$1, $16, $1
	addiu	$2, $zero, 1
	sw	$2, 0($1)
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$18, 28($sp)
	lw	$19, 32($sp)
	lw	$ra, 36($sp)
	jr	$ra
	addiu	$sp, $sp, 40
	.set	at
	.set	macro
	.set	reorder
	.end	computerMove
$func_end2:
	.size	computerMove, ($func_end2)-computerMove

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,56,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -56
	sw	$ra, 52($sp)
	addiu	$1, $zero, 1
	sw	$1, 16($sp)
	sw	$zero, 28($sp)
	sw	$zero, 40($sp)
	sw	$zero, 20($sp)
	addiu	$2, $zero, -1
	sw	$2, 32($sp)
	sw	$1, 44($sp)
	addiu	$4, $sp, 16
	sw	$zero, 24($sp)
	sw	$zero, 36($sp)
	jal	computerMove
	sw	$zero, 48($sp)
	lw	$2, 32($sp)
	lw	$ra, 52($sp)
	jr	$ra
	addiu	$sp, $sp, 56
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end3:
	.size	main, ($func_end3)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
