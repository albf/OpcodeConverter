	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/matrix.c"
	.text
	.globl	memset
	.align	2
	.type	memset,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	memset
memset:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	beqz	$6, $BB0_3
	nop
	move	 $2, $4
$BB0_2:
	sb	$5, 0($2)
	addiu	$6, $6, -1
	bnez	$6, $BB0_2
	addiu	$2, $2, 1
$BB0_3:
	jr	$ra
	move	 $2, $4
	.set	at
	.set	macro
	.set	reorder
	.end	memset
$func_end0:
	.size	memset, ($func_end0)-memset

	.globl	my_malloc
	.align	2
	.type	my_malloc,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	my_malloc
my_malloc:
	.frame	$sp,24,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$ra, 20($sp)
	lui	$3, %hi(curptr)
	lw	$2, %lo(curptr)($3)
	addu	$4, $2, $4
	slti	$1, $4, 257
	bnez	$1, $BB1_3
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB1_2:
	j	$BB1_2
	nop
$BB1_3:
	sw	$4, %lo(curptr)($3)
	lui	$1, %hi(mypool)
	addiu	$1, $1, %lo(mypool)
	addu	$2, $1, $2
	lw	$ra, 20($sp)
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	my_malloc
$func_end1:
	.size	my_malloc, ($func_end1)-my_malloc

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,32,$ra
	.mask 	0x80030000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -32
	sw	$ra, 28($sp)
	sw	$17, 24($sp)
	sw	$16, 20($sp)
	lui	$2, %hi(curptr)
	lw	$4, %lo(curptr)($2)
	addiu	$3, $4, 12
	slti	$1, $3, 257
	bnez	$1, $BB2_3
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_2:
	j	$BB2_2
	nop
$BB2_3:
	lui	$1, %hi(mypool)
	sw	$3, %lo(curptr)($2)
	addiu	$7, $1, %lo(mypool)
	addiu	$5, $4, 24
	slti	$1, $5, 257
	beqz	$1, $BB2_6
	addu	$2, $7, $4
	lui	$6, %hi(curptr)
	sw	$5, %lo(curptr)($6)
	addu	$1, $7, $3
	sw	$1, 0($2)
	sw	$zero, 0($1)
	addiu	$3, $zero, 1
	sw	$3, 4($1)
	addiu	$3, $zero, 2
	sw	$3, 8($1)
	addiu	$3, $4, 36
	slti	$1, $3, 257
	beqz	$1, $BB2_6
	nop
	sw	$3, %lo(curptr)($6)
	lui	$1, %hi(mypool)
	addiu	$6, $1, %lo(mypool)
	addu	$1, $6, $5
	sw	$1, 4($2)
	addiu	$5, $zero, 3
	sw	$5, 0($1)
	addiu	$5, $zero, 4
	sw	$5, 4($1)
	addiu	$5, $zero, 5
	sw	$5, 8($1)
	addiu	$5, $4, 48
	slti	$1, $5, 257
	bnez	$1, $BB2_8
	nop
$BB2_6:
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_7:
	j	$BB2_7
	nop
$BB2_8:
	lui	$8, %hi(curptr)
	sw	$5, %lo(curptr)($8)
	addu	$1, $6, $3
	sw	$1, 8($2)
	addiu	$3, $zero, 6
	sw	$3, 0($1)
	addiu	$3, $zero, 7
	sw	$3, 4($1)
	addiu	$3, $zero, 8
	sw	$3, 8($1)
	addiu	$7, $4, 60
	slti	$1, $7, 257
	bnez	$1, $BB2_11
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_10:
	j	$BB2_10
	nop
$BB2_11:
	lui	$1, %hi(mypool)
	sw	$7, %lo(curptr)($8)
	addiu	$9, $1, %lo(mypool)
	addiu	$3, $4, 72
	slti	$1, $3, 257
	beqz	$1, $BB2_14
	addu	$6, $9, $5
	lui	$8, %hi(curptr)
	sw	$3, %lo(curptr)($8)
	addu	$1, $9, $7
	sw	$1, 0($6)
	sw	$zero, 0($1)
	addiu	$5, $zero, 1
	sw	$5, 4($1)
	addiu	$5, $zero, 2
	sw	$5, 8($1)
	addiu	$5, $4, 84
	slti	$1, $5, 257
	beqz	$1, $BB2_14
	nop
	sw	$5, %lo(curptr)($8)
	lui	$1, %hi(mypool)
	addiu	$7, $1, %lo(mypool)
	addu	$1, $7, $3
	sw	$1, 4($6)
	addiu	$3, $zero, 3
	sw	$3, 0($1)
	addiu	$3, $zero, 4
	sw	$3, 4($1)
	addiu	$3, $zero, 5
	sw	$3, 8($1)
	addiu	$3, $4, 96
	slti	$1, $3, 257
	bnez	$1, $BB2_16
	nop
$BB2_14:
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_15:
	j	$BB2_15
	nop
$BB2_16:
	lui	$8, %hi(curptr)
	sw	$3, %lo(curptr)($8)
	addu	$1, $7, $5
	sw	$1, 8($6)
	addiu	$5, $zero, 6
	sw	$5, 0($1)
	addiu	$5, $zero, 7
	sw	$5, 4($1)
	addiu	$5, $zero, 8
	sw	$5, 8($1)
	addiu	$5, $4, 108
	slti	$1, $5, 257
	bnez	$1, $BB2_19
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_18:
	j	$BB2_18
	nop
$BB2_19:
	lui	$1, %hi(mypool)
	sw	$5, %lo(curptr)($8)
	addiu	$5, $1, %lo(mypool)
	addiu	$1, $4, 120
	slti	$1, $1, 257
	beqz	$1, $BB2_24
	nop
	addu	$3, $5, $3
	addu	$7, $5, $4
	addiu	$5, $zero, 0
	addiu	$8, $zero, 96
	addiu	$10, $zero, 0
	addiu	$9, $zero, 0
$BB2_21:
	addu	$1, $7, $8
	addu	$11, $7, $5
	addiu	$12, $11, 108
	sw	$12, 0($1)
	sw	$10, 108($11)
	addiu	$1, $10, 1
	sw	$1, 112($11)
	addiu	$10, $10, 2
	addiu	$9, $9, 1
	slti	$1, $9, 3
	beqz	$1, $BB2_26
	sw	$10, 116($11)
	addiu	$5, $5, 12
	addu	$11, $4, $5
	addiu	$8, $8, 4
	addiu	$1, $11, 120
	slti	$1, $1, 257
	bnez	$1, $BB2_21
	addiu	$10, $10, 1
	addiu	$1, $11, 108
	lui	$2, %hi(curptr)
	sw	$1, %lo(curptr)($2)
$BB2_24:
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_25:
	j	$BB2_25
	nop
$BB2_26:
	addu	$1, $4, $5
	addiu	$1, $1, 120
	lui	$7, %hi(curptr)
	sw	$1, %lo(curptr)($7)
	lw	$1, 8($2)
	lw	$5, 4($2)
	lw	$8, 0($2)
	lw	$9, 8($6)
	addiu	$10, $zero, 9
	sw	$10, 8($9)
	addiu	$11, $zero, 10
	sw	$11, 4($9)
	addiu	$12, $zero, 11
	addiu	$13, $zero, 8
	addiu	$14, $zero, 7
	addiu	$15, $zero, 6
	addiu	$24, $zero, 5
	addiu	$25, $zero, 4
	addiu	$gp, $zero, 3
	addiu	$16, $zero, 2
	addiu	$17, $zero, 1
	sw	$zero, 0($9)
	lw	$9, 4($6)
	sw	$17, 8($9)
	sw	$16, 4($9)
	sw	$gp, 0($9)
	lw	$9, 0($6)
	sw	$25, 8($9)
	sw	$24, 4($9)
	sw	$15, 0($9)
	sw	$gp, 0($8)
	sw	$25, 4($8)
	sw	$24, 8($8)
	sw	$15, 0($5)
	sw	$14, 4($5)
	sw	$13, 8($5)
	sw	$10, 0($1)
	sw	$11, 4($1)
	sw	$12, 8($1)
	lw	$5, %lo(curptr)($7)
	addiu	$8, $5, 12
	slti	$1, $8, 257
	bnez	$1, $BB2_29
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_28:
	j	$BB2_28
	nop
$BB2_29:
	sw	$8, %lo(curptr)($7)
	lui	$1, %hi(mypool)
	addiu	$7, $1, %lo(mypool)
	addiu	$1, $5, 24
	slti	$1, $1, 257
	beqz	$1, $BB2_34
	nop
	addu	$8, $7, $5
	addiu	$7, $zero, 0
	addiu	$9, $zero, 0
	addiu	$11, $zero, 0
	addiu	$10, $zero, 0
$BB2_31:
	addu	$1, $8, $7
	addu	$12, $8, $9
	addiu	$13, $12, 12
	sw	$13, 0($1)
	sw	$11, 12($12)
	addiu	$1, $11, 1
	sw	$1, 16($12)
	addiu	$11, $11, 2
	addiu	$10, $10, 1
	slti	$1, $10, 3
	beqz	$1, $BB2_36
	sw	$11, 20($12)
	addiu	$9, $9, 12
	addu	$12, $5, $9
	addiu	$7, $7, 4
	addiu	$1, $12, 24
	slti	$1, $1, 257
	bnez	$1, $BB2_31
	addiu	$11, $11, 1
	addiu	$1, $12, 12
	lui	$2, %hi(curptr)
	sw	$1, %lo(curptr)($2)
$BB2_34:
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB2_35:
	j	$BB2_35
	nop
$BB2_36:
	addu	$1, $5, $9
	addiu	$1, $1, 24
	lui	$7, %hi(curptr)
	sw	$1, %lo(curptr)($7)
	lui	$1, %hi(mypool)
	addiu	$1, $1, %lo(mypool)
	addu	$7, $4, $1
	addu	$4, $5, $1
	lw	$1, 8($6)
	lw	$9, 0($6)
	lw	$10, 0($2)
	addiu	$4, $4, 4
	addiu	$5, $7, 4
	lw	$11, 0($10)
	lw	$12, 0($9)
	lw	$13, 8($10)
	lw	$14, 0($1)
	addiu	$7, $zero, 0
	lw	$15, 0($8)
	mul	$13, $14, $13
	mul	$11, $12, $11
	lw	$12, 4($10)
	lw	$6, 4($6)
	lw	$14, 0($6)
	mul	$12, $14, $12
	addu	$11, $12, $11
	addu	$11, $13, $11
	sw	$11, 0($15)
	lw	$11, 0($10)
	lw	$12, 4($9)
	lw	$13, 8($10)
	lw	$14, 4($1)
	mul	$13, $14, $13
	mul	$11, $12, $11
	lw	$12, 4($10)
	lw	$14, 4($6)
	mul	$12, $14, $12
	addu	$11, $12, $11
	addu	$11, $13, $11
	sw	$11, 4($15)
	lw	$11, 0($10)
	lw	$12, 8($9)
	lw	$13, 8($10)
	lw	$14, 8($1)
	mul	$13, $14, $13
	mul	$11, $12, $11
	lw	$10, 4($10)
	lw	$12, 8($6)
	mul	$10, $12, $10
	addu	$10, $10, $11
	addu	$10, $13, $10
	sw	$10, 8($15)
	lw	$10, 0($9)
	lw	$11, 4($2)
	lw	$12, 0($11)
	lw	$13, 0($1)
	lw	$14, 8($11)
	mul	$13, $13, $14
	mul	$10, $10, $12
	lw	$12, 0($6)
	lw	$14, 4($11)
	mul	$12, $12, $14
	lw	$14, 4($8)
	addu	$10, $12, $10
	addu	$10, $13, $10
	sw	$10, 0($14)
	lw	$10, 0($11)
	lw	$12, 4($9)
	lw	$13, 8($11)
	lw	$15, 4($1)
	mul	$13, $15, $13
	mul	$10, $12, $10
	lw	$12, 4($11)
	lw	$15, 4($6)
	mul	$12, $15, $12
	addu	$10, $12, $10
	addu	$10, $13, $10
	sw	$10, 4($14)
	lw	$10, 0($11)
	lw	$12, 8($9)
	lw	$13, 8($11)
	lw	$15, 8($1)
	mul	$13, $15, $13
	mul	$10, $12, $10
	lw	$11, 4($11)
	lw	$12, 8($6)
	mul	$11, $12, $11
	addu	$10, $11, $10
	addu	$10, $13, $10
	sw	$10, 8($14)
	lw	$10, 0($9)
	lw	$11, 8($2)
	lw	$12, 0($11)
	lw	$13, 0($1)
	lw	$14, 8($11)
	mul	$13, $13, $14
	mul	$10, $10, $12
	lw	$12, 0($6)
	lw	$14, 4($11)
	mul	$12, $12, $14
	lw	$14, 8($8)
	addu	$10, $12, $10
	addu	$10, $13, $10
	sw	$10, 0($14)
	lw	$10, 0($11)
	lw	$12, 4($9)
	lw	$13, 8($11)
	lw	$15, 4($1)
	mul	$13, $15, $13
	mul	$10, $12, $10
	lw	$12, 4($11)
	lw	$15, 4($6)
	mul	$12, $15, $12
	addu	$10, $12, $10
	addu	$10, $13, $10
	sw	$10, 4($14)
	lw	$10, 0($11)
	lw	$12, 8($9)
	lw	$13, 8($11)
	lw	$15, 8($1)
	mul	$13, $15, $13
	mul	$10, $12, $10
	lw	$11, 4($11)
	lw	$12, 8($6)
	mul	$11, $12, $11
	addu	$10, $11, $10
	addu	$10, $13, $10
	sw	$10, 8($14)
	lw	$10, 0($9)
	lw	$11, 0($2)
	lw	$12, 0($11)
	addu	$12, $10, $12
	lw	$10, 0($8)
	sw	$12, 0($10)
	lw	$12, 4($11)
	lw	$13, 4($9)
	addu	$12, $13, $12
	sw	$12, 4($10)
	lw	$12, 8($11)
	lw	$9, 8($9)
	addu	$9, $9, $12
	sw	$9, 8($10)
	lw	$9, 0($6)
	lw	$12, 4($2)
	lw	$13, 0($12)
	addu	$9, $9, $13
	lw	$13, 4($8)
	sw	$9, 0($13)
	lw	$9, 4($12)
	lw	$14, 4($6)
	addu	$9, $14, $9
	sw	$9, 4($13)
	lw	$9, 8($12)
	lw	$6, 8($6)
	addu	$6, $6, $9
	sw	$6, 8($13)
	lw	$6, 0($1)
	lw	$2, 8($2)
	lw	$9, 0($2)
	addu	$6, $6, $9
	lw	$8, 8($8)
	sw	$6, 0($8)
	lw	$6, 4($2)
	lw	$9, 4($1)
	addu	$6, $9, $6
	sw	$6, 4($8)
	lw	$2, 8($2)
	lw	$1, 8($1)
	addu	$1, $1, $2
	sw	$1, 8($8)
	lw	$2, 8($3)
	lw	$6, 4($3)
	lw	$3, 0($3)
	addiu	$8, $zero, 12
	j	$BB2_38
	move	 $9, $10
$BB2_37:
	addu	$1, $5, $7
	lw	$11, 0($1)
	addu	$1, $4, $7
	lw	$9, 0($1)
	move	 $7, $12
$BB2_38:
	lw	$1, 0($11)
	lw	$12, 0($3)
	lw	$13, 8($11)
	lw	$14, 0($2)
	mul	$13, $14, $13
	mul	$1, $12, $1
	lw	$12, 4($11)
	lw	$14, 0($6)
	mul	$14, $14, $12
	addiu	$12, $7, 4
	addu	$1, $14, $1
	addu	$1, $13, $1
	sw	$1, 0($9)
	lw	$1, 0($11)
	lw	$13, 4($3)
	lw	$14, 8($11)
	lw	$15, 4($2)
	mul	$14, $15, $14
	mul	$1, $13, $1
	lw	$13, 4($11)
	lw	$15, 4($6)
	mul	$13, $15, $13
	addu	$1, $13, $1
	addu	$1, $14, $1
	sw	$1, 4($9)
	lw	$1, 0($11)
	lw	$13, 8($3)
	lw	$14, 8($11)
	lw	$15, 8($2)
	mul	$14, $15, $14
	mul	$1, $13, $1
	lw	$11, 4($11)
	lw	$13, 8($6)
	mul	$11, $13, $11
	addu	$1, $11, $1
	addu	$1, $14, $1
	bne	$12, $8, $BB2_37
	sw	$1, 8($9)
	lw	$2, 0($10)
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$ra, 28($sp)
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end2:
	.size	main, ($func_end2)-main

	.globl	mkmatrix
	.align	2
	.type	mkmatrix,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	mkmatrix
mkmatrix:
	.frame	$sp,24,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$ra, 20($sp)
	lui	$2, %hi(curptr)
	lw	$8, %lo(curptr)($2)
	sll	$9, $4, 2
	addu	$12, $8, $9
	slti	$1, $12, 257
	bnez	$1, $BB3_3
	nop
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB3_2:
	j	$BB3_2
	nop
$BB3_3:
	sw	$12, %lo(curptr)($2)
	lui	$1, %hi(mypool)
	addiu	$1, $1, %lo(mypool)
	blez	$4, $BB3_14
	addu	$2, $1, $8
	sll	$3, $5, 2
	addu	$13, $12, $3
	slti	$1, $13, 257
	beqz	$1, $BB3_11
	nop
	slti	$1, $5, 1
	addiu	$6, $zero, 0
	move	 $7, $5
	movn	$7, $zero, $1
	addu	$1, $8, $9
	lui	$8, %hi(mypool)
	addiu	$8, $8, %lo(mypool)
	addu	$9, $8, $1
	addiu	$10, $zero, 0
$BB3_6:
	move	 $11, $13
	sll	$1, $10, 2
	addu	$1, $2, $1
	addu	$12, $8, $12
	sw	$12, 0($1)
	move	 $12, $9
	blez	$5, $BB3_8
	addiu	$13, $zero, 0
$BB3_7:
	addu	$1, $6, $13
	sw	$1, 0($12)
	addiu	$13, $13, 1
	bne	$5, $13, $BB3_7
	addiu	$12, $12, 4
$BB3_8:
	addiu	$10, $10, 1
	slt	$1, $10, $4
	beqz	$1, $BB3_13
	nop
	addu	$9, $9, $3
	addu	$6, $6, $7
	addu	$13, $11, $3
	slti	$1, $13, 257
	bnez	$1, $BB3_6
	move	 $12, $11
	lui	$1, %hi(curptr)
	sw	$11, %lo(curptr)($1)
$BB3_11:
	lui	$1, %hi($.str)
	jal	print
	addiu	$4, $1, %lo($.str)
$BB3_12:
	j	$BB3_12
	nop
$BB3_13:
	lui	$1, %hi(curptr)
	sw	$11, %lo(curptr)($1)
$BB3_14:
	lw	$ra, 20($sp)
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	mkmatrix
$func_end3:
	.size	mkmatrix, ($func_end3)-mkmatrix

	.globl	initialize
	.align	2
	.type	initialize,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	initialize
initialize:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lw	$1, 8($4)
	lw	$2, 4($4)
	lw	$3, 0($4)
	lw	$4, 8($5)
	addiu	$6, $zero, 9
	sw	$6, 8($4)
	addiu	$7, $zero, 10
	sw	$7, 4($4)
	sw	$zero, 0($4)
	lw	$4, 4($5)
	addiu	$8, $zero, 11
	addiu	$9, $zero, 8
	addiu	$10, $zero, 7
	addiu	$11, $zero, 6
	addiu	$12, $zero, 5
	addiu	$13, $zero, 4
	addiu	$14, $zero, 3
	addiu	$15, $zero, 2
	addiu	$24, $zero, 1
	sw	$24, 8($4)
	sw	$15, 4($4)
	sw	$14, 0($4)
	lw	$4, 0($5)
	sw	$13, 8($4)
	sw	$12, 4($4)
	sw	$11, 0($4)
	sw	$14, 0($3)
	sw	$13, 4($3)
	sw	$12, 8($3)
	sw	$11, 0($2)
	sw	$10, 4($2)
	sw	$9, 8($2)
	sw	$6, 0($1)
	sw	$7, 4($1)
	jr	$ra
	sw	$8, 8($1)
	.set	at
	.set	macro
	.set	reorder
	.end	initialize
$func_end4:
	.size	initialize, ($func_end4)-initialize

	.globl	mmult
	.align	2
	.type	mmult,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	mmult
mmult:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lw	$2, 16($sp)
	blez	$4, $BB5_8
	nop
	addiu	$3, $zero, 0
$BB5_2:
	blez	$5, $BB5_7
	nop
	sll	$1, $3, 2
	addu	$8, $6, $1
	lw	$8, 0($8)
	addu	$1, $2, $1
	lw	$9, 0($1)
	addiu	$10, $zero, 0
$BB5_4:
	move	 $11, $5
	move	 $13, $7
	move	 $14, $8
	addiu	$12, $zero, 0
$BB5_5:
	lw	$1, 0($13)
	sll	$15, $10, 2
	addu	$1, $1, $15
	lw	$1, 0($1)
	lw	$24, 0($14)
	addiu	$11, $11, -1
	addiu	$13, $13, 4
	addiu	$14, $14, 4
	mul	$1, $1, $24
	bnez	$11, $BB5_5
	addu	$12, $1, $12
	addu	$1, $9, $15
	addiu	$10, $10, 1
	bne	$10, $5, $BB5_4
	sw	$12, 0($1)
$BB5_7:
	addiu	$3, $3, 1
	bne	$3, $4, $BB5_2
	nop
$BB5_8:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	mmult
$func_end5:
	.size	mmult, ($func_end5)-mmult

	.globl	sum
	.align	2
	.type	sum,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	sum
sum:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	blez	$4, $BB6_6
	nop
	lw	$2, 16($sp)
	addiu	$3, $zero, 0
$BB6_2:
	blez	$5, $BB6_5
	nop
	sll	$1, $3, 2
	addu	$8, $2, $1
	lw	$8, 0($8)
	addu	$9, $7, $1
	lw	$9, 0($9)
	addu	$1, $6, $1
	lw	$10, 0($1)
	move	 $11, $5
$BB6_4:
	lw	$1, 0($10)
	lw	$12, 0($9)
	addu	$1, $12, $1
	sw	$1, 0($8)
	addiu	$11, $11, -1
	addiu	$8, $8, 4
	addiu	$9, $9, 4
	bnez	$11, $BB6_4
	addiu	$10, $10, 4
$BB6_5:
	addiu	$3, $3, 1
	bne	$3, $4, $BB6_2
	nop
$BB6_6:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	sum
$func_end6:
	.size	sum, ($func_end6)-sum

	.globl	zeromatrix
	.align	2
	.type	zeromatrix,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	zeromatrix
zeromatrix:
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
	move	 $16, $6
	move	 $18, $4
	blez	$18, $BB7_5
	move	 $17, $5
	sll	$19, $17, 2
$BB7_2:
	blez	$17, $BB7_4
	nop
	lw	$4, 0($16)
	addiu	$5, $zero, 0
	jal	memset
	move	 $6, $19
$BB7_4:
	addiu	$18, $18, -1
	bnez	$18, $BB7_2
	addiu	$16, $16, 4
$BB7_5:
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
	.end	zeromatrix
$func_end7:
	.size	zeromatrix, ($func_end7)-zeromatrix

	.type	curptr,@object
	.bss
	.globl	curptr
	.align	2
curptr:
	.4byte	0
	.size	curptr, 4

	.type	$.str,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
$.str:
	.asciz	"out of memory :-)\n"
	.size	$.str, 19

	.type	mypool,@object
	.comm	mypool,256,1

	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
