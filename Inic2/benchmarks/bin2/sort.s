	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/sort.c"
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,832,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -832
	sw	$ra, 828($sp)
	sw	$16, 824($sp)
	addiu	$2, $sp, 16
	addiu	$4, $2, 4
	addiu	$3, $sp, 420
	addiu	$6, $3, 4
	addiu	$8, $zero, 1
	lui	$1, 26214
	ori	$5, $1, 26215
	addiu	$7, $zero, 101
$BB0_1:
	mult	$8, $5
	mfhi	$1
	addiu	$9, $4, 4
	addiu	$10, $6, 4
	addiu	$11, $8, 1
	srl	$12, $1, 31
	sra	$1, $1, 1
	addu	$1, $1, $12
	sll	$12, $1, 2
	addu	$1, $12, $1
	subu	$1, $8, $1
	sw	$1, 0($6)
	sw	$1, 0($4)
	move	 $4, $9
	move	 $6, $10
	bne	$11, $7, $BB0_1
	move	 $8, $11
	addiu	$4, $zero, 51
	addiu	$5, $zero, 100
	j	$BB0_4
	addiu	$6, $zero, 1
$BB0_3:
	sll	$1, $9, 2
	addu	$1, $3, $1
	sw	$16, 0($1)
$BB0_4:
	slti	$1, $4, 2
	bnez	$1, $BB0_6
	nop
	addiu	$4, $4, -1
	sll	$1, $4, 2
	addu	$1, $3, $1
	lw	$16, 0($1)
	j	$BB0_7
	nop
$BB0_6:
	sll	$1, $5, 2
	addu	$1, $3, $1
	lw	$16, 0($1)
	lw	$7, 424($sp)
	addiu	$5, $5, -1
	beq	$5, $6, $BB0_15
	sw	$7, 0($1)
$BB0_7:
	sll	$8, $4, 1
	slt	$1, $5, $8
	move	 $7, $4
	bnez	$1, $BB0_3
	move	 $9, $4
$BB0_8:
	slt	$1, $8, $5
	beqz	$1, $BB0_10
	nop
	sll	$1, $8, 2
	addu	$1, $3, $1
	lw	$1, 0($1)
	ori	$9, $8, 1
	sll	$10, $9, 2
	addu	$10, $3, $10
	lw	$10, 0($10)
	sltu	$1, $1, $10
	movn	$8, $9, $1
	j	$BB0_11
	move	 $9, $8
$BB0_10:
	move	 $9, $8
$BB0_11:
	sll	$1, $9, 2
	addu	$1, $3, $1
	lw	$8, 0($1)
	sltu	$1, $16, $8
	beqz	$1, $BB0_14
	nop
	sll	$1, $7, 2
	addu	$1, $3, $1
	sw	$8, 0($1)
	sll	$8, $9, 1
	slt	$1, $5, $8
	beqz	$1, $BB0_8
	move	 $7, $9
	j	$BB0_3
	nop
$BB0_14:
	j	$BB0_3
	move	 $9, $7
$BB0_15:
	sw	$16, 424($sp)
	addiu	$3, $zero, 0
	addiu	$4, $zero, 100
$BB0_16:
	subu	$5, $4, $3
	addiu	$6, $zero, 1
	j	$BB0_18
	addiu	$7, $zero, 0
$BB0_17:
	sw	$11, -4($9)
	sw	$10, 0($9)
	addiu	$7, $zero, 1
$BB0_18:
	sll	$1, $6, 2
	addu	$8, $2, $1
$BB0_19:
	slt	$1, $6, $5
	beqz	$1, $BB0_22
	nop
	addiu	$9, $8, 4
	lw	$10, 0($8)
	lw	$11, 4($8)
	sltu	$1, $11, $10
	addiu	$6, $6, 1
	beqz	$1, $BB0_19
	move	 $8, $9
	j	$BB0_17
	nop
$BB0_22:
	bnez	$7, $BB0_16
	addiu	$3, $3, 1
	addiu	$4, $sp, 16
	addiu	$5, $zero, 0
	jal	quicksort
	addiu	$6, $zero, 100
	lw	$1, 20($sp)
	addu	$2, $1, $16
	lw	$16, 824($sp)
	lw	$ra, 828($sp)
	jr	$ra
	addiu	$sp, $sp, 832
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
	addiu	$2, $5, -1
	addiu	$3, $zero, 0
$BB2_1:
	subu	$5, $2, $3
	addiu	$6, $zero, 1
	j	$BB2_3
	addiu	$7, $zero, 0
$BB2_2:
	sw	$10, -4($8)
	sw	$9, 0($8)
	addiu	$7, $zero, 1
$BB2_3:
	sll	$1, $6, 2
	addu	$8, $4, $1
$BB2_4:
	slt	$1, $6, $5
	beqz	$1, $BB2_7
	nop
	lw	$9, 0($8)
	lw	$10, 4($8)
	sltu	$1, $10, $9
	addiu	$8, $8, 4
	beqz	$1, $BB2_4
	addiu	$6, $6, 1
	j	$BB2_2
	nop
$BB2_7:
	bnez	$7, $BB2_1
	addiu	$3, $3, 1
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	bubble_sort
$func_end2:
	.size	bubble_sort, ($func_end2)-bubble_sort

	.globl	quicksort
	.align	2
	.type	quicksort,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	quicksort
quicksort:
	.frame	$sp,48,$ra
	.mask 	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -48
	sw	$ra, 44($sp)
	sw	$21, 40($sp)
	sw	$20, 36($sp)
	sw	$19, 32($sp)
	sw	$18, 28($sp)
	sw	$17, 24($sp)
	sw	$16, 20($sp)
	move	 $16, $6
	slt	$1, $5, $16
	beqz	$1, $BB3_14
	move	 $17, $4
	sll	$1, $16, 2
	addu	$18, $17, $1
	addiu	$19, $17, 4
	addiu	$20, $17, -4
$BB3_2:
	slt	$1, $5, $16
	beqz	$1, $BB3_12
	nop
	sll	$1, $5, 2
	addu	$2, $17, $1
	move	 $8, $5
	j	$BB3_5
	move	 $21, $16
$BB3_4:
	sw	$8, 0($3)
	sw	$7, 0($9)
	move	 $8, $4
$BB3_5:
	sll	$1, $8, 2
	addu	$3, $20, $1
	lw	$6, 0($2)
$BB3_6:
	move	 $4, $8
	slt	$1, $4, $16
	lw	$7, 4($3)
	beqz	$1, $BB3_8
	addiu	$3, $3, 4
	sltu	$1, $6, $7
	beqz	$1, $BB3_6
	addiu	$8, $4, 1
$BB3_8:
	sll	$1, $21, 2
	addu	$9, $19, $1
	addiu	$21, $21, 1
$BB3_9:
	lw	$8, -4($9)
	sltu	$1, $6, $8
	addiu	$9, $9, -4
	bnez	$1, $BB3_9
	addiu	$21, $21, -1
	slt	$1, $4, $21
	bnez	$1, $BB3_4
	nop
	j	$BB3_13
	nop
$BB3_12:
	sll	$1, $5, 2
	addu	$2, $17, $1
	lw	$8, 0($18)
	move	 $21, $16
$BB3_13:
	lw	$1, 0($2)
	sw	$8, 0($2)
	sll	$2, $21, 2
	addu	$2, $17, $2
	sw	$1, 0($2)
	addiu	$6, $21, -1
	jal	quicksort
	move	 $4, $17
	addiu	$5, $21, 1
	slt	$1, $5, $16
	bnez	$1, $BB3_2
	nop
$BB3_14:
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$18, 28($sp)
	lw	$19, 32($sp)
	lw	$20, 36($sp)
	lw	$21, 40($sp)
	lw	$ra, 44($sp)
	jr	$ra
	addiu	$sp, $sp, 48
	.set	at
	.set	macro
	.set	reorder
	.end	quicksort
$func_end3:
	.size	quicksort, ($func_end3)-quicksort


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
