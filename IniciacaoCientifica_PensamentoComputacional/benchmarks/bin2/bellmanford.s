	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/bellmanford.c"
	.text
	.globl	relax
	.align	2
	.type	relax,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	relax
relax:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	sll	$1, $4, 2
	addu	$1, $7, $1
	lw	$1, 0($1)
	addu	$2, $1, $6
	sll	$3, $5, 2
	addu	$5, $7, $3
	lw	$1, 0($5)
	slt	$1, $2, $1
	beqz	$1, $BB0_2
	nop
	lw	$1, 16($sp)
	sw	$2, 0($5)
	addu	$1, $1, $3
	sw	$4, 0($1)
$BB0_2:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	relax
$func_end0:
	.size	relax, ($func_end0)-relax

	.globl	initialize_single_source
	.align	2
	.type	initialize_single_source,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	initialize_single_source
initialize_single_source:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	blez	$7, $BB1_3
	nop
	addiu	$2, $5, 4
	addiu	$3, $4, 4
	lui	$1, 15
	ori	$5, $1, 16960
$BB1_2:
	sw	$5, 0($3)
	sw	$zero, 0($2)
	addiu	$2, $2, 4
	addiu	$7, $7, -1
	bnez	$7, $BB1_2
	addiu	$3, $3, 4
$BB1_3:
	sll	$1, $6, 2
	addu	$1, $4, $1
	jr	$ra
	sw	$zero, 0($1)
	.set	at
	.set	macro
	.set	reorder
	.end	initialize_single_source
$func_end1:
	.size	initialize_single_source, ($func_end1)-initialize_single_source

	.globl	bellman_ford
	.align	2
	.type	bellman_ford,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	bellman_ford
bellman_ford:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lw	$8, 28($sp)
	lw	$9, 24($sp)
	lw	$3, 16($sp)
	blez	$8, $BB2_22
	nop
	lw	$2, 20($sp)
	addiu	$10, $3, 4
	addiu	$11, $2, 4
	lui	$1, 15
	ori	$12, $1, 16960
	move	 $13, $8
$BB2_2:
	sw	$12, 0($10)
	sw	$zero, 0($11)
	addiu	$10, $10, 4
	addiu	$13, $13, -1
	bnez	$13, $BB2_2
	addiu	$11, $11, 4
	sll	$1, $9, 2
	addu	$1, $3, $1
	sw	$zero, 0($1)
	slti	$1, $8, 2
	bnez	$1, $BB2_13
	nop
	addiu	$9, $zero, 1
$BB2_5:
	blez	$8, $BB2_12
	addiu	$11, $zero, 1
$BB2_6:
	move	 $10, $11
	sll	$11, $10, 2
	addu	$1, $4, $11
	lw	$12, 0($1)
	blez	$12, $BB2_11
	nop
	addu	$11, $3, $11
$BB2_8:
	sll	$12, $12, 2
	addu	$1, $5, $12
	lw	$1, 0($1)
	addu	$13, $7, $12
	lw	$13, 0($13)
	lw	$14, 0($11)
	addu	$13, $14, $13
	sll	$14, $1, 2
	addu	$15, $3, $14
	lw	$1, 0($15)
	slt	$1, $13, $1
	beqz	$1, $BB2_10
	nop
	sw	$13, 0($15)
	addu	$1, $2, $14
	sw	$10, 0($1)
$BB2_10:
	addu	$1, $6, $12
	lw	$12, 0($1)
	bgtz	$12, $BB2_8
	nop
$BB2_11:
	bne	$10, $8, $BB2_6
	addiu	$11, $10, 1
$BB2_12:
	addiu	$9, $9, 1
	bne	$9, $8, $BB2_5
	nop
$BB2_13:
	blez	$8, $BB2_23
	nop
	addiu	$9, $zero, 1
$BB2_15:
	sll	$10, $9, 2
	addu	$1, $4, $10
	lw	$2, 0($1)
	blez	$2, $BB2_19
	nop
	addu	$1, $3, $10
	lw	$10, 0($1)
$BB2_17:
	sll	$11, $2, 2
	addu	$1, $5, $11
	lw	$1, 0($1)
	addu	$2, $7, $11
	lw	$2, 0($2)
	addu	$12, $2, $10
	sll	$1, $1, 2
	addu	$1, $3, $1
	lw	$1, 0($1)
	slt	$1, $12, $1
	bnez	$1, $BB2_21
	addiu	$2, $zero, 0
	addu	$1, $6, $11
	lw	$2, 0($1)
	bgtz	$2, $BB2_17
	nop
$BB2_19:
	slt	$1, $9, $8
	bnez	$1, $BB2_15
	addiu	$9, $9, 1
	addiu	$2, $zero, 1
$BB2_21:
	jr	$ra
	nop
$BB2_22:
	sll	$1, $9, 2
	addu	$1, $3, $1
	sw	$zero, 0($1)
	jr	$ra
	addiu	$2, $zero, 1
$BB2_23:
	jr	$ra
	addiu	$2, $zero, 1
	.set	at
	.set	macro
	.set	reorder
	.end	bellman_ford
$func_end2:
	.size	bellman_ford, ($func_end2)-bellman_ford

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,520,$ra
	.mask 	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -520
	sw	$ra, 516($sp)
	sw	$fp, 512($sp)
	sw	$23, 508($sp)
	sw	$22, 504($sp)
	sw	$21, 500($sp)
	sw	$20, 496($sp)
	sw	$19, 492($sp)
	sw	$18, 488($sp)
	sw	$17, 484($sp)
	sw	$16, 480($sp)
	addiu	$1, $zero, 1
	sw	$1, 440($sp)
	addiu	$7, $zero, 24
	addiu	$6, $zero, 20
	addiu	$5, $zero, 18
	addiu	$4, $zero, 14
	addiu	$gp, $zero, 12
	addiu	$24, $zero, 9
	addiu	$21, $zero, 7
	addiu	$18, $zero, 6
	addiu	$20, $zero, 3
	addiu	$12, $zero, 5
	addiu	$15, $zero, 4
	addiu	$16, $zero, 2
	addiu	$2, $zero, 10
	addiu	$13, $zero, 8
	addiu	$23, $zero, -3
	addiu	$fp, $zero, -2
	addiu	$ra, $zero, -4
	addiu	$3, $zero, 25
	addiu	$8, $zero, 23
	addiu	$9, $zero, 22
	addiu	$10, $zero, 21
	addiu	$11, $zero, 19
	addiu	$14, $zero, 17
	addiu	$25, $zero, 16
	addiu	$17, $zero, 15
	addiu	$19, $zero, 13
	sw	$20, 444($sp)
	sw	$18, 448($sp)
	sw	$21, 452($sp)
	sw	$24, 456($sp)
	sw	$gp, 460($sp)
	addiu	$22, $zero, 11
	sw	$4, 464($sp)
	addiu	$4, $sp, 436
	sw	$5, 468($sp)
	addiu	$5, $sp, 332
	sw	$6, 472($sp)
	addiu	$6, $sp, 228
	sw	$7, 476($sp)
	sw	$16, 336($sp)
	sw	$15, 340($sp)
	sw	$20, 344($sp)
	sw	$15, 348($sp)
	sw	$12, 352($sp)
	sw	$16, 356($sp)
	sw	$20, 360($sp)
	sw	$12, 364($sp)
	sw	$1, 368($sp)
	sw	$20, 372($sp)
	sw	$18, 376($sp)
	sw	$21, 380($sp)
	sw	$13, 384($sp)
	sw	$24, 388($sp)
	sw	$2, 392($sp)
	sw	$1, 396($sp)
	sw	$16, 400($sp)
	sw	$24, 404($sp)
	sw	$15, 408($sp)
	sw	$2, 412($sp)
	sw	$16, 416($sp)
	sw	$2, 420($sp)
	sw	$12, 424($sp)
	sw	$15, 428($sp)
	sw	$20, 432($sp)
	sw	$18, 84($sp)
	sw	$21, 88($sp)
	sw	$12, 92($sp)
	sw	$13, 96($sp)
	sw	$ra, 100($sp)
	addiu	$ra, $sp, 36
	sw	$fp, 104($sp)
	addiu	$fp, $sp, 184
	sw	$23, 108($sp)
	sw	$24, 112($sp)
	sw	$16, 116($sp)
	sw	$21, 120($sp)
	sw	$15, 124($sp)
	sw	$16, 128($sp)
	sw	$24, 132($sp)
	sw	$1, 136($sp)
	sw	$12, 140($sp)
	sw	$20, 144($sp)
	sw	$15, 148($sp)
	sw	$24, 152($sp)
	sw	$18, 156($sp)
	sw	$gp, 160($sp)
	sw	$1, 164($sp)
	sw	$24, 168($sp)
	sw	$16, 172($sp)
	sw	$1, 176($sp)
	sw	$15, 180($sp)
	sw	$16, 232($sp)
	sw	$zero, 236($sp)
	sw	$15, 240($sp)
	sw	$12, 244($sp)
	sw	$zero, 248($sp)
	sw	$zero, 252($sp)
	sw	$13, 256($sp)
	sw	$zero, 260($sp)
	sw	$2, 264($sp)
	sw	$22, 268($sp)
	sw	$zero, 272($sp)
	sw	$19, 276($sp)
	sw	$zero, 280($sp)
	sw	$17, 284($sp)
	sw	$25, 288($sp)
	sw	$14, 292($sp)
	sw	$zero, 296($sp)
	sw	$11, 300($sp)
	sw	$zero, 304($sp)
	sw	$10, 308($sp)
	sw	$9, 312($sp)
	sw	$8, 316($sp)
	sw	$zero, 320($sp)
	sw	$3, 324($sp)
	sw	$zero, 328($sp)
	sw	$2, 28($sp)
	sw	$1, 24($sp)
	sw	$fp, 20($sp)
	sw	$ra, 16($sp)
	jal	bellman_ford
	addiu	$7, $sp, 80
	lw	$1, 188($sp)
	lw	$2, 40($sp)
	addu	$1, $2, $1
	lw	$2, 44($sp)
	addu	$1, $2, $1
	lw	$2, 192($sp)
	addu	$1, $1, $2
	lw	$2, 48($sp)
	addu	$1, $2, $1
	lw	$2, 204($sp)
	lw	$3, 56($sp)
	lw	$4, 200($sp)
	lw	$5, 52($sp)
	lw	$6, 196($sp)
	addu	$1, $1, $6
	addu	$1, $5, $1
	addu	$1, $1, $4
	addu	$1, $3, $1
	addu	$2, $1, $2
	lw	$16, 480($sp)
	lw	$17, 484($sp)
	lw	$18, 488($sp)
	lw	$19, 492($sp)
	lw	$20, 496($sp)
	lw	$21, 500($sp)
	lw	$22, 504($sp)
	lw	$23, 508($sp)
	lw	$fp, 512($sp)
	lw	$ra, 516($sp)
	jr	$ra
	addiu	$sp, $sp, 520
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end3:
	.size	main, ($func_end3)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
