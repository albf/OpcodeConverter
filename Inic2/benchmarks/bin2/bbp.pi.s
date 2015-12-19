	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/bbp.pi.c"
	.section	.rodata.cst4,"aM",@progbits,4
	.align	2
$CPI0_0:
	.4byte	1036831949
$CPI0_1:
	.4byte	1056964608
	.text
	.globl	sqrt2
	.align	2
	.type	sqrt2,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	sqrt2
sqrt2:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	mtc1	$zero, $f0
	c.ult.s	$f12, $f0
	bc1t	 $BB0_3
	nop
	lui	$1, %hi($CPI0_0)
	lwc1	$f1, %lo($CPI0_0)($1)
$BB0_2:
	add.s	$f0, $f0, $f1
	mul.s	$f2, $f0, $f0
	c.ole.s	$f2, $f12
	bc1t	 $BB0_2
	nop
$BB0_3:
	div.s	$f1, $f12, $f0
	lui	$1, %hi($CPI0_1)
	lwc1	$f2, %lo($CPI0_1)($1)
	add.s	$f0, $f0, $f1
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	mul.s	$f1, $f0, $f2
	div.s	$f1, $f12, $f1
	madd.s	$f0, $f1, $f0, $f2
	jr	$ra
	mul.s	$f0, $f0, $f2
	.set	at
	.set	macro
	.set	reorder
	.end	sqrt2
$func_end0:
	.size	sqrt2, ($func_end0)-sqrt2

	.globl	mod
	.align	2
	.type	mod,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	mod
mod:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	neg.d	$f0, $f12
	mtc1	$zero, $f2
	mthc1	$zero, $f2
	c.olt.d	$f12, $f2
	movt.d	$f12, $f0, $fcc0
	jr	$ra
	mov.d	$f0, $f12
	.set	at
	.set	macro
	.set	reorder
	.end	mod
$func_end1:
	.size	mod, ($func_end1)-mod

	.globl	fmod
	.align	2
	.type	fmod,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	fmod
fmod:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	neg.d	$f2, $f14
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	c.olt.d	$f14, $f4
	mov.d	$f0, $f14
	movt.d	$f0, $f2, $fcc0
	neg.d	$f6, $f12
	c.olt.d	$f12, $f4
	mov.d	$f2, $f12
	movt.d	$f2, $f6, $fcc0
	mul.d	$f6, $f12, $f14
	c.ule.d	$f6, $f4
	bc1t	 $BB2_4
	nop
	c.ule.d	$f2, $f0
	bc1t	 $BB2_6
	nop
$BB2_2:
	sub.d	$f12, $f12, $f14
	neg.d	$f2, $f12
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	c.olt.d	$f12, $f4
	mov.d	$f4, $f12
	movt.d	$f4, $f2, $fcc0
	c.ule.d	$f4, $f0
	bc1f	 $BB2_2
	nop
	j	$BB2_6
	nop
$BB2_4:
	c.ule.d	$f2, $f0
	bc1t	 $BB2_6
	nop
$BB2_5:
	add.d	$f12, $f12, $f14
	neg.d	$f2, $f12
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	c.olt.d	$f12, $f4
	mov.d	$f4, $f12
	movt.d	$f4, $f2, $fcc0
	c.ule.d	$f4, $f0
	bc1f	 $BB2_5
	nop
$BB2_6:
	jr	$ra
	mov.d	$f0, $f12
	.set	at
	.set	macro
	.set	reorder
	.end	fmod
$func_end2:
	.size	fmod, ($func_end2)-fmod

	.globl	inv_mod
	.align	2
	.type	inv_mod,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	inv_mod
inv_mod:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$6, $zero, 1
	addiu	$2, $zero, 0
	move	 $7, $5
$BB3_1:
	move	 $3, $6
	move	 $1, $7
	div	$zero, $1, $4
	teq	$4, $zero, 7
	mflo	$6
	mul	$7, $6, $3
	mul	$8, $6, $4
	subu	$9, $1, $8
	subu	$6, $2, $7
	move	 $7, $4
	move	 $2, $3
	bne	$1, $8, $BB3_1
	move	 $4, $9
	div	$zero, $3, $5
	teq	$5, $zero, 7
	mfhi	$1
	sra	$2, $1, 31
	and	$2, $2, $5
	jr	$ra
	addu	$2, $2, $1
	.set	at
	.set	macro
	.set	reorder
	.end	inv_mod
$func_end3:
	.size	inv_mod, ($func_end3)-inv_mod

	.globl	pow_mod
	.align	2
	.type	pow_mod,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	pow_mod
pow_mod:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	mtc1	$6, $f0
	cvt.d.w	$f0, $f0
	neg.d	$f4, $f0
	slti	$1, $6, 0
	mov.d	$f2, $f0
	movn.d	$f2, $f4, $1
	j	$BB4_2
	addiu	$2, $zero, 1
$BB4_1:
	trunc.w.d	$f4, $f4
	mfc1	$4, $f4
$BB4_2:
	andi	$1, $5, 1
	beqz	$1, $BB4_10
	nop
	mtc1	$4, $f4
	cvt.d.w	$f4, $f4
	mtc1	$2, $f6
	cvt.d.w	$f6, $f6
	mul.d	$f4, $f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	neg.d	$f10, $f4
	c.olt.d	$f4, $f8
	mov.d	$f6, $f4
	movt.d	$f6, $f10, $fcc0
	mul.d	$f10, $f0, $f4
	c.ule.d	$f10, $f8
	bc1t	 $BB4_7
	nop
	c.ule.d	$f6, $f2
	bc1t	 $BB4_9
	nop
$BB4_5:
	sub.d	$f4, $f4, $f0
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f2
	bc1f	 $BB4_5
	nop
	j	$BB4_9
	nop
$BB4_7:
	c.ule.d	$f6, $f2
	bc1t	 $BB4_9
	nop
$BB4_8:
	add.d	$f4, $f0, $f4
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f2
	bc1f	 $BB4_8
	nop
$BB4_9:
	trunc.w.d	$f4, $f4
	mfc1	$2, $f4
$BB4_10:
	sra	$5, $5, 1
	beqz	$5, $BB4_18
	nop
	mtc1	$4, $f4
	cvt.d.w	$f4, $f4
	mul.d	$f4, $f4, $f4
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	mul.d	$f8, $f0, $f4
	c.ule.d	$f8, $f6
	bc1t	 $BB4_15
	nop
	c.ule.d	$f4, $f2
	bc1t	 $BB4_1
	nop
$BB4_13:
	sub.d	$f4, $f4, $f0
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f2
	bc1f	 $BB4_13
	nop
	j	$BB4_1
	nop
$BB4_15:
	c.ule.d	$f4, $f2
	bc1t	 $BB4_1
	nop
$BB4_16:
	add.d	$f4, $f0, $f4
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f2
	bc1f	 $BB4_16
	nop
	j	$BB4_1
	nop
$BB4_18:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	pow_mod
$func_end4:
	.size	pow_mod, ($func_end4)-pow_mod

	.section	.rodata.cst4,"aM",@progbits,4
	.align	2
$CPI5_0:
	.4byte	1036831949
$CPI5_1:
	.4byte	1056964608
	.text
	.globl	is_prime
	.align	2
	.type	is_prime,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	is_prime
is_prime:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	andi	$1, $4, 1
	beqz	$1, $BB5_10
	addiu	$2, $zero, 0
	mtc1	$4, $f0
	cvt.s.w	$f0, $f0
	bltz	$4, $BB5_4
	mtc1	$zero, $f1
	lui	$1, %hi($CPI5_0)
	lwc1	$f2, %lo($CPI5_0)($1)
$BB5_3:
	add.s	$f1, $f1, $f2
	mul.s	$f3, $f1, $f1
	c.ole.s	$f3, $f0
	bc1t	 $BB5_3
	nop
$BB5_4:
	div.s	$f2, $f0, $f1
	lui	$1, %hi($CPI5_1)
	lwc1	$f3, %lo($CPI5_1)($1)
	add.s	$f1, $f1, $f2
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f2, $f0, $f2
	madd.s	$f1, $f2, $f1, $f3
	mul.s	$f2, $f1, $f3
	div.s	$f0, $f0, $f2
	madd.s	$f0, $f0, $f1, $f3
	mul.s	$f0, $f0, $f3
	trunc.w.s	$f0, $f0
	mfc1	$3, $f0
	slti	$1, $3, 3
	beqz	$1, $BB5_6
	nop
	jr	$ra
	addiu	$2, $zero, 1
$BB5_6:
	addiu	$5, $zero, 3
$BB5_7:
	div	$zero, $4, $5
	teq	$5, $zero, 7
	mfhi	$1
	beqz	$1, $BB5_10
	nop
	addiu	$5, $5, 2
	slt	$1, $3, $5
	beqz	$1, $BB5_7
	nop
	jr	$ra
	addiu	$2, $zero, 1
$BB5_10:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	is_prime
$func_end5:
	.size	is_prime, ($func_end5)-is_prime

	.globl	next_prime
	.align	2
	.type	next_prime,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	next_prime
next_prime:
	.frame	$sp,24,$ra
	.mask 	0x80010000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$ra, 20($sp)
	sw	$16, 16($sp)
	move	 $16, $4
$BB6_1:
	addiu	$16, $16, 1
	jal	is_prime
	move	 $4, $16
	beqz	$2, $BB6_1
	nop
	move	 $2, $16
	lw	$16, 16($sp)
	lw	$ra, 20($sp)
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	next_prime
$func_end6:
	.size	next_prime, ($func_end6)-next_prime

	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
$CPI7_0:
	.8byte	4617640077784605801
$CPI7_1:
	.8byte	4607182418800017408
$CPI7_2:
	.8byte	-4616189618054758400
$CPI7_3:
	.8byte	4741671816366391296
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,88,$ra
	.mask 	0x800f0000,-52
	.fmask	0xfff00000,-8
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -88
	sdc1	$f30, 80($sp)
	sdc1	$f28, 72($sp)
	sdc1	$f26, 64($sp)
	sdc1	$f24, 56($sp)
	sdc1	$f22, 48($sp)
	sdc1	$f20, 40($sp)
	sw	$ra, 36($sp)
	sw	$19, 32($sp)
	sw	$18, 28($sp)
	sw	$17, 24($sp)
	sw	$16, 20($sp)
	mtc1	$zero, $f22
	mthc1	$zero, $f22
	addiu	$16, $zero, 3
	lui	$1, %hi($CPI7_0)
	ldc1	$f24, %lo($CPI7_0)($1)
	lui	$1, %hi($CPI7_1)
	ldc1	$f26, %lo($CPI7_1)($1)
	addiu	$17, $zero, 100
	lui	$18, %hi($CPI7_2)
$BB7_1:
	mtc1	$16, $f20
	cvt.d.w	$f20, $f20
	jal	log
	mov.d	$f12, $f20
	div.d	$f0, $f24, $f0
	addiu	$2, $zero, 1
	trunc.w.d	$f0, $f0
	mfc1	$3, $f0
	addiu	$6, $zero, 1
	blez	$3, $BB7_3
	move	 $4, $3
$BB7_2:
	addiu	$4, $4, -1
	bnez	$4, $BB7_2
	mul	$6, $6, $16
$BB7_3:
	mtc1	$6, $f28
	cvt.d.w	$f28, $f28
	neg.d	$f0, $f28
	slti	$1, $6, 0
	mov.d	$f30, $f28
	movn.d	$f30, $f0, $1
	addiu	$19, $zero, 0
	addiu	$4, $zero, 0
	addiu	$7, $zero, 1
	mov.d	$f0, $f26
	addiu	$5, $zero, 1
	addiu	$8, $zero, 1
	addiu	$9, $zero, 1
$BB7_4:
	slt	$1, $7, $16
	bnez	$1, $BB7_6
	move	 $10, $5
$BB7_5:
	div	$zero, $10, $16
	teq	$16, $zero, 7
	mflo	$10
	div	$zero, $10, $16
	teq	$16, $zero, 7
	mfhi	$1
	addiu	$4, $4, -1
	beqz	$1, $BB7_5
	addiu	$7, $zero, 0
$BB7_6:
	mtc1	$10, $f2
	cvt.d.w	$f2, $f2
	mtc1	$9, $f4
	cvt.d.w	$f4, $f4
	mul.d	$f2, $f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	neg.d	$f8, $f2
	c.olt.d	$f2, $f6
	mov.d	$f4, $f2
	movt.d	$f4, $f8, $fcc0
	mul.d	$f8, $f28, $f2
	c.ule.d	$f8, $f6
	bc1t	 $BB7_10
	nop
	c.ule.d	$f4, $f30
	bc1t	 $BB7_12
	nop
$BB7_8:
	sub.d	$f2, $f2, $f28
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_8
	nop
	j	$BB7_12
	nop
$BB7_10:
	c.ule.d	$f4, $f30
	bc1t	 $BB7_12
	nop
$BB7_11:
	add.d	$f2, $f28, $f2
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_11
	nop
$BB7_12:
	slt	$1, $2, $16
	sll	$9, $5, 1
	bnez	$1, $BB7_16
	addiu	$9, $9, -1
	bne	$2, $16, $BB7_15
	nop
$BB7_14:
	div	$zero, $9, $16
	teq	$16, $zero, 7
	mflo	$9
	div	$zero, $9, $16
	teq	$16, $zero, 7
	mfhi	$1
	beqz	$1, $BB7_14
	addiu	$4, $4, 1
$BB7_15:
	subu	$2, $2, $16
$BB7_16:
	trunc.w.d	$f2, $f2
	mtc1	$9, $f4
	cvt.d.w	$f4, $f4
	mtc1	$8, $f6
	cvt.d.w	$f6, $f6
	mul.d	$f4, $f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	neg.d	$f10, $f4
	c.olt.d	$f4, $f8
	mov.d	$f6, $f4
	movt.d	$f6, $f10, $fcc0
	mul.d	$f10, $f28, $f4
	c.ule.d	$f10, $f8
	bc1t	 $BB7_20
	nop
	c.ule.d	$f6, $f30
	bc1t	 $BB7_22
	nop
$BB7_18:
	sub.d	$f4, $f4, $f28
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f30
	bc1f	 $BB7_18
	nop
	j	$BB7_22
	nop
$BB7_20:
	c.ule.d	$f6, $f30
	bc1t	 $BB7_22
	nop
$BB7_21:
	add.d	$f4, $f28, $f4
	neg.d	$f6, $f4
	mtc1	$zero, $f8
	mthc1	$zero, $f8
	c.olt.d	$f4, $f8
	mov.d	$f8, $f4
	movt.d	$f8, $f6, $fcc0
	c.ule.d	$f8, $f30
	bc1f	 $BB7_21
	nop
$BB7_22:
	mfc1	$9, $f2
	trunc.w.d	$f2, $f4
	blez	$4, $BB7_46
	mfc1	$8, $f2
	addiu	$13, $zero, 1
	addiu	$10, $zero, 0
	move	 $14, $6
	move	 $12, $8
$BB7_24:
	move	 $11, $13
	move	 $1, $14
	div	$zero, $1, $12
	teq	$12, $zero, 7
	mflo	$13
	mul	$14, $13, $11
	mul	$15, $13, $12
	subu	$24, $1, $15
	subu	$13, $10, $14
	move	 $14, $12
	move	 $10, $11
	bne	$1, $15, $BB7_24
	move	 $12, $24
	div	$zero, $11, $6
	teq	$6, $zero, 7
	mfhi	$1
	mtc1	$9, $f2
	cvt.d.w	$f2, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	sra	$10, $1, 31
	and	$10, $10, $6
	addu	$1, $10, $1
	mtc1	$1, $f4
	cvt.d.w	$f4, $f4
	mul.d	$f2, $f2, $f4
	neg.d	$f8, $f2
	c.olt.d	$f2, $f6
	mov.d	$f4, $f2
	movt.d	$f4, $f8, $fcc0
	mul.d	$f8, $f28, $f2
	c.ule.d	$f8, $f6
	bc1t	 $BB7_29
	nop
	c.ule.d	$f4, $f30
	bc1t	 $BB7_31
	nop
$BB7_27:
	sub.d	$f2, $f2, $f28
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_27
	nop
	j	$BB7_31
	nop
$BB7_29:
	c.ule.d	$f4, $f30
	bc1t	 $BB7_31
	nop
$BB7_30:
	add.d	$f2, $f28, $f2
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_30
	nop
$BB7_31:
	trunc.w.d	$f2, $f2
	mfc1	$1, $f2
	mtc1	$1, $f2
	cvt.d.w	$f2, $f2
	mul.d	$f2, $f0, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	neg.d	$f8, $f2
	c.olt.d	$f2, $f6
	mov.d	$f4, $f2
	movt.d	$f4, $f8, $fcc0
	mul.d	$f8, $f28, $f2
	c.ule.d	$f8, $f6
	bc1t	 $BB7_35
	nop
	c.ule.d	$f4, $f30
	bc1t	 $BB7_37
	nop
$BB7_33:
	sub.d	$f2, $f2, $f28
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_33
	nop
	j	$BB7_37
	nop
$BB7_35:
	c.ule.d	$f4, $f30
	bc1t	 $BB7_37
	nop
$BB7_36:
	add.d	$f2, $f28, $f2
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_36
	nop
$BB7_37:
	slt	$1, $4, $3
	trunc.w.d	$f2, $f2
	mfc1	$11, $f2
	beqz	$1, $BB7_45
	move	 $10, $4
$BB7_38:
	mtc1	$11, $f2
	cvt.d.w	$f2, $f2
	mul.d	$f2, $f20, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	neg.d	$f8, $f2
	c.olt.d	$f2, $f6
	mov.d	$f4, $f2
	movt.d	$f4, $f8, $fcc0
	mul.d	$f8, $f28, $f2
	c.ule.d	$f8, $f6
	bc1t	 $BB7_42
	nop
	c.ule.d	$f4, $f30
	bc1t	 $BB7_44
	nop
$BB7_40:
	sub.d	$f2, $f2, $f28
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_40
	nop
	j	$BB7_44
	nop
$BB7_42:
	c.ule.d	$f4, $f30
	bc1t	 $BB7_44
	nop
$BB7_43:
	add.d	$f2, $f28, $f2
	neg.d	$f4, $f2
	mtc1	$zero, $f6
	mthc1	$zero, $f6
	c.olt.d	$f2, $f6
	mov.d	$f6, $f2
	movt.d	$f6, $f4, $fcc0
	c.ule.d	$f6, $f30
	bc1f	 $BB7_43
	nop
$BB7_44:
	addiu	$10, $10, 1
	trunc.w.d	$f2, $f2
	bne	$10, $3, $BB7_38
	mfc1	$11, $f2
$BB7_45:
	addu	$1, $11, $19
	slt	$10, $1, $6
	move	 $11, $6
	movn	$11, $zero, $10
	subu	$19, $1, $11
$BB7_46:
	addiu	$7, $7, 1
	addiu	$2, $2, 2
	addiu	$5, $5, 1
	bne	$5, $17, $BB7_4
	add.d	$f0, $f0, $f26
	addiu	$4, $zero, 10
	jal	pow_mod
	addiu	$5, $zero, 9
	mtc1	$2, $f0
	cvt.d.w	$f0, $f0
	mtc1	$19, $f2
	cvt.d.w	$f2, $f2
	mul.d	$f0, $f2, $f0
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	neg.d	$f6, $f0
	c.olt.d	$f0, $f4
	mov.d	$f2, $f0
	movt.d	$f2, $f6, $fcc0
	mul.d	$f6, $f28, $f0
	c.ule.d	$f6, $f4
	bc1t	 $BB7_51
	nop
	c.ule.d	$f2, $f30
	bc1t	 $BB7_53
	nop
$BB7_49:
	sub.d	$f0, $f0, $f28
	neg.d	$f2, $f0
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	c.olt.d	$f0, $f4
	mov.d	$f4, $f0
	movt.d	$f4, $f2, $fcc0
	c.ule.d	$f4, $f30
	bc1f	 $BB7_49
	nop
	j	$BB7_53
	nop
$BB7_51:
	c.ule.d	$f2, $f30
	bc1t	 $BB7_53
	nop
$BB7_52:
	add.d	$f0, $f28, $f0
	neg.d	$f2, $f0
	mtc1	$zero, $f4
	mthc1	$zero, $f4
	c.olt.d	$f0, $f4
	mov.d	$f4, $f0
	movt.d	$f4, $f2, $fcc0
	c.ule.d	$f4, $f30
	bc1f	 $BB7_52
	nop
$BB7_53:
	trunc.w.d	$f0, $f0
	mfc1	$1, $f0
	mtc1	$1, $f0
	cvt.d.w	$f0, $f0
	div.d	$f0, $f0, $f28
	mtc1	$zero, $f2
	mthc1	$zero, $f2
	add.d	$f22, $f22, $f0
	neg.d	$f4, $f22
	c.olt.d	$f22, $f2
	mov.d	$f0, $f22
	movt.d	$f0, $f4, $fcc0
	c.ule.d	$f22, $f2
	bc1t	 $BB7_57
	nop
	c.ule.d	$f0, $f26
	bc1t	 $BB7_59
	nop
$BB7_55:
	ldc1	$f0, %lo($CPI7_2)($18)
	add.d	$f22, $f22, $f0
	mtc1	$zero, $f0
	mthc1	$zero, $f0
	neg.d	$f2, $f22
	c.olt.d	$f22, $f0
	mov.d	$f0, $f22
	movt.d	$f0, $f2, $fcc0
	c.ule.d	$f0, $f26
	bc1f	 $BB7_55
	nop
	j	$BB7_59
	nop
$BB7_57:
	c.ule.d	$f0, $f26
	bc1t	 $BB7_59
	nop
$BB7_58:
	add.d	$f22, $f22, $f26
	mtc1	$zero, $f0
	mthc1	$zero, $f0
	neg.d	$f2, $f22
	c.olt.d	$f22, $f0
	mov.d	$f0, $f22
	movt.d	$f0, $f2, $fcc0
	c.ule.d	$f0, $f26
	bc1f	 $BB7_58
	nop
$BB7_59:
	addiu	$16, $16, 1
	jal	is_prime
	move	 $4, $16
	beqz	$2, $BB7_59
	nop
	slti	$1, $16, 199
	bnez	$1, $BB7_1
	nop
	lui	$1, %hi($CPI7_3)
	ldc1	$f0, %lo($CPI7_3)($1)
	mul.d	$f0, $f22, $f0
	lui	$1, %hi($.str)
	addiu	$4, $1, %lo($.str)
	trunc.w.d	$f0, $f0
	mfc1	$6, $f0
	jal	printf
	addiu	$5, $zero, 10
	trunc.w.d	$f0, $f22
	mfc1	$2, $f0
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$18, 28($sp)
	lw	$19, 32($sp)
	lw	$ra, 36($sp)
	ldc1	$f20, 40($sp)
	ldc1	$f22, 48($sp)
	ldc1	$f24, 56($sp)
	ldc1	$f26, 64($sp)
	ldc1	$f28, 72($sp)
	ldc1	$f30, 80($sp)
	jr	$ra
	addiu	$sp, $sp, 88
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end7:
	.size	main, ($func_end7)-main

	.type	$.str,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
$.str:
	.asciz	"Decimal digits of pi at position %d: %09d\n"
	.size	$.str, 43


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
