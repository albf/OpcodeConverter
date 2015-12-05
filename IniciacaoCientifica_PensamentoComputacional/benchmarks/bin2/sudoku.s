	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/sudoku.c"
	.text
	.globl	isAvailable
	.align	2
	.type	isAvailable,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	isAvailable
isAvailable:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$1, 21845
	ori	$3, $1, 21846
	mult	$5, $3
	mfhi	$1
	mult	$6, $3
	mfhi	$2
	sll	$6, $6, 2
	addu	$6, $4, $6
	sll	$8, $5, 2
	sll	$5, $5, 5
	addu	$5, $5, $8
	addu	$5, $4, $5
	addiu	$8, $zero, 0
	srl	$9, $2, 31
	addu	$2, $2, $9
	sll	$9, $2, 1
	addu	$9, $9, $2
	srl	$2, $1, 31
	addu	$1, $1, $2
	sll	$2, $1, 1
	addu	$10, $2, $1
$BB0_1:
	lw	$1, 0($5)
	beq	$1, $7, $BB0_6
	nop
	lw	$1, 0($6)
	beq	$1, $7, $BB0_7
	nop
	mult	$8, $3
	mfhi	$1
	srl	$2, $1, 31
	addu	$1, $1, $2
	sll	$2, $1, 1
	addu	$2, $2, $1
	subu	$2, $8, $2
	addu	$2, $10, $2
	sll	$11, $2, 2
	sll	$2, $2, 5
	addu	$2, $2, $11
	addu	$2, $4, $2
	addu	$1, $9, $1
	sll	$1, $1, 2
	addu	$1, $2, $1
	lw	$1, 0($1)
	beq	$1, $7, $BB0_8
	nop
	addiu	$8, $8, 1
	addiu	$6, $6, 36
	addiu	$5, $5, 4
	slti	$1, $8, 9
	bnez	$1, $BB0_1
	addiu	$2, $zero, 1
	j	$BB0_9
	nop
$BB0_6:
	jr	$ra
	addiu	$2, $zero, 0
$BB0_7:
	jr	$ra
	addiu	$2, $zero, 0
$BB0_8:
	addiu	$2, $zero, 0
$BB0_9:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	isAvailable
$func_end0:
	.size	isAvailable, ($func_end0)-isAvailable

	.globl	fillSudoku
	.align	2
	.type	fillSudoku,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	fillSudoku
fillSudoku:
	.frame	$sp,72,$ra
	.mask 	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -72
	sw	$ra, 68($sp)
	sw	$fp, 64($sp)
	sw	$23, 60($sp)
	sw	$22, 56($sp)
	sw	$21, 52($sp)
	sw	$20, 48($sp)
	sw	$19, 44($sp)
	sw	$18, 40($sp)
	sw	$17, 36($sp)
	sw	$16, 32($sp)
	move	 $16, $5
	move	 $17, $4
	sll	$1, $16, 2
	sll	$2, $16, 5
	addu	$1, $2, $1
	addu	$3, $17, $1
	addiu	$2, $zero, 1
$BB1_1:
	sll	$1, $6, 2
	addu	$20, $3, $1
$BB1_2:
	slti	$1, $16, 9
	beqz	$1, $BB1_22
	nop
	slti	$1, $6, 9
	beqz	$1, $BB1_23
	nop
	lw	$1, 0($20)
	beqz	$1, $BB1_8
	nop
	addiu	$6, $6, 1
	slti	$1, $6, 9
	bnez	$1, $BB1_2
	addiu	$20, $20, 4
	addiu	$3, $3, 36
	addiu	$16, $16, 1
	slti	$1, $16, 9
	bnez	$1, $BB1_1
	addiu	$6, $zero, 0
	j	$BB1_24
	nop
$BB1_8:
	lui	$1, 21845
	ori	$21, $1, 21846
	mult	$16, $21
	mfhi	$1
	mult	$6, $21
	mfhi	$2
	sll	$3, $16, 2
	sll	$4, $16, 5
	addu	$3, $4, $3
	sll	$4, $6, 2
	addu	$22, $17, $4
	addu	$23, $17, $3
	addiu	$4, $6, 1
	sw	$4, 24($sp)
	addiu	$5, $16, 1
	sw	$5, 16($sp)
	addiu	$fp, $zero, 0
	srl	$3, $2, 31
	addu	$2, $2, $3
	sll	$3, $2, 1
	addu	$19, $3, $2
	srl	$2, $1, 31
	addu	$1, $1, $2
	sll	$2, $1, 1
	addu	$18, $2, $1
	slti	$1, $4, 9
	sw	$1, 28($sp)
	slti	$1, $5, 9
	sw	$1, 20($sp)
$BB1_9:
	addiu	$fp, $fp, 1
	move	 $2, $23
	move	 $3, $22
	addiu	$4, $zero, 0
$BB1_10:
	lw	$1, 0($2)
	beq	$1, $fp, $BB1_20
	nop
	lw	$1, 0($3)
	beq	$1, $fp, $BB1_20
	nop
	mult	$4, $21
	mfhi	$1
	srl	$5, $1, 31
	addu	$1, $1, $5
	sll	$5, $1, 1
	addu	$5, $5, $1
	subu	$5, $4, $5
	addu	$5, $18, $5
	sll	$6, $5, 2
	sll	$5, $5, 5
	addu	$5, $5, $6
	addu	$5, $17, $5
	addu	$1, $19, $1
	sll	$1, $1, 2
	addu	$1, $5, $1
	lw	$1, 0($1)
	beq	$1, $fp, $BB1_20
	nop
	addiu	$4, $4, 1
	addiu	$2, $2, 4
	slti	$1, $4, 9
	bnez	$1, $BB1_10
	addiu	$3, $3, 36
	sw	$fp, 0($20)
	lw	$1, 28($sp)
	beqz	$1, $BB1_17
	nop
	move	 $4, $17
	lw	$6, 24($sp)
	jal	fillSudoku
	move	 $5, $16
	bnez	$2, $BB1_25
	nop
	j	$BB1_20
	sw	$zero, 0($20)
$BB1_17:
	lw	$1, 20($sp)
	beqz	$1, $BB1_26
	nop
	move	 $4, $17
	lw	$5, 16($sp)
	jal	fillSudoku
	addiu	$6, $zero, 0
	bnez	$2, $BB1_27
	nop
	sw	$zero, 0($20)
$BB1_20:
	slti	$1, $fp, 9
	bnez	$1, $BB1_9
	addiu	$2, $zero, 0
	j	$BB1_24
	nop
$BB1_22:
	j	$BB1_24
	addiu	$2, $zero, 1
$BB1_23:
	addiu	$2, $zero, 1
$BB1_24:
	lw	$16, 32($sp)
	lw	$17, 36($sp)
	lw	$18, 40($sp)
	lw	$19, 44($sp)
	lw	$20, 48($sp)
	lw	$21, 52($sp)
	lw	$22, 56($sp)
	lw	$23, 60($sp)
	lw	$fp, 64($sp)
	lw	$ra, 68($sp)
	jr	$ra
	addiu	$sp, $sp, 72
$BB1_25:
	j	$BB1_24
	addiu	$2, $zero, 1
$BB1_26:
	j	$BB1_24
	addiu	$2, $zero, 1
$BB1_27:
	j	$BB1_24
	addiu	$2, $zero, 1
	.set	at
	.set	macro
	.set	reorder
	.end	fillSudoku
$func_end1:
	.size	fillSudoku, ($func_end1)-fillSudoku

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,344,$ra
	.mask 	0x80000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -344
	sw	$ra, 340($sp)
	sw	$zero, 40($sp)
	sw	$zero, 36($sp)
	sw	$zero, 32($sp)
	sw	$zero, 28($sp)
	sw	$zero, 24($sp)
	sw	$zero, 20($sp)
	sw	$zero, 16($sp)
	addiu	$6, $zero, 9
	sw	$6, 44($sp)
	sw	$zero, 48($sp)
	addiu	$1, $zero, 1
	sw	$1, 52($sp)
	sw	$6, 56($sp)
	sw	$zero, 60($sp)
	addiu	$2, $zero, 7
	addiu	$3, $zero, 4
	addiu	$7, $zero, 2
	addiu	$8, $zero, 5
	addiu	$5, $zero, 8
	addiu	$9, $zero, 6
	addiu	$10, $zero, 3
	addiu	$4, $sp, 16
	sw	$3, 64($sp)
	sw	$2, 68($sp)
	sw	$zero, 72($sp)
	sw	$9, 76($sp)
	sw	$zero, 80($sp)
	sw	$5, 84($sp)
	sw	$zero, 88($sp)
	sw	$8, 92($sp)
	sw	$7, 96($sp)
	sw	$5, 100($sp)
	sw	$1, 104($sp)
	sw	$6, 108($sp)
	sw	$3, 112($sp)
	sw	$zero, 116($sp)
	sw	$2, 120($sp)
	sw	$7, 124($sp)
	sw	$zero, 128($sp)
	sw	$zero, 132($sp)
	sw	$zero, 136($sp)
	sw	$3, 140($sp)
	sw	$5, 144($sp)
	sw	$zero, 164($sp)
	sw	$zero, 160($sp)
	sw	$zero, 156($sp)
	sw	$zero, 152($sp)
	sw	$zero, 148($sp)
	sw	$6, 168($sp)
	sw	$zero, 172($sp)
	sw	$zero, 176($sp)
	sw	$zero, 180($sp)
	sw	$8, 184($sp)
	sw	$zero, 204($sp)
	sw	$zero, 200($sp)
	sw	$zero, 196($sp)
	sw	$zero, 192($sp)
	sw	$zero, 188($sp)
	sw	$2, 208($sp)
	sw	$8, 212($sp)
	sw	$zero, 216($sp)
	sw	$zero, 220($sp)
	sw	$zero, 224($sp)
	sw	$6, 228($sp)
	sw	$6, 232($sp)
	sw	$zero, 236($sp)
	sw	$2, 240($sp)
	sw	$10, 244($sp)
	sw	$9, 248($sp)
	sw	$3, 252($sp)
	sw	$1, 256($sp)
	sw	$5, 260($sp)
	sw	$zero, 264($sp)
	sw	$8, 268($sp)
	sw	$zero, 272($sp)
	sw	$9, 276($sp)
	sw	$zero, 280($sp)
	sw	$5, 284($sp)
	sw	$1, 288($sp)
	sw	$zero, 292($sp)
	sw	$2, 296($sp)
	sw	$3, 300($sp)
	sw	$zero, 304($sp)
	sw	$5, 308($sp)
	sw	$zero, 336($sp)
	sw	$zero, 332($sp)
	sw	$zero, 328($sp)
	sw	$zero, 324($sp)
	sw	$zero, 320($sp)
	sw	$zero, 316($sp)
	sw	$zero, 312($sp)
	addiu	$5, $zero, 0
	jal	fillSudoku
	addiu	$6, $zero, 0
	addiu	$2, $zero, 0
	lw	$ra, 340($sp)
	jr	$ra
	addiu	$sp, $sp, 344
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end2:
	.size	main, ($func_end2)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
