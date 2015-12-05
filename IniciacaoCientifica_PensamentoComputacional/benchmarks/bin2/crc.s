	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/crc.c"
	.text
	.globl	reverse
	.align	2
	.type	reverse,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	reverse
reverse:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	srl	$1, $4, 1
	lui	$2, 21845
	ori	$2, $2, 21845
	and	$1, $1, $2
	sll	$2, $4, 1
	lui	$3, 43690
	ori	$3, $3, 43690
	and	$2, $2, $3
	or	$1, $2, $1
	srl	$2, $1, 2
	lui	$3, 13107
	ori	$3, $3, 13107
	and	$2, $2, $3
	sll	$1, $1, 2
	lui	$3, 52428
	ori	$3, $3, 52428
	and	$1, $1, $3
	or	$1, $1, $2
	lui	$2, 61680
	lui	$3, 3855
	lui	$4, 255
	srl	$5, $1, 4
	ori	$3, $3, 3855
	and	$3, $5, $3
	sll	$1, $1, 4
	ori	$2, $2, 61680
	and	$1, $1, $2
	or	$1, $1, $3
	sll	$2, $1, 24
	srl	$3, $1, 24
	or	$2, $3, $2
	sll	$3, $1, 8
	and	$3, $3, $4
	or	$2, $2, $3
	srl	$1, $1, 8
	andi	$1, $1, 65280
	jr	$ra
	or	$2, $2, $1
	.set	at
	.set	macro
	.set	reorder
	.end	reverse
$func_end0:
	.size	reverse, ($func_end0)-reverse

	.globl	crc32a
	.align	2
	.type	crc32a,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	crc32a
crc32a:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lbu	$3, 0($4)
	beqz	$3, $BB1_4
	addiu	$2, $zero, 0
	addiu	$4, $4, 1
	addiu	$5, $zero, -1
	lui	$1, 1217
	ori	$2, $1, 7607
$BB1_2:
	sll	$1, $5, 1
	xor	$6, $1, $2
	andi	$3, $3, 255
	sll	$7, $3, 31
	xor	$5, $5, $7
	slti	$5, $5, 0
	movn	$1, $6, $5
	sll	$5, $1, 1
	xor	$6, $5, $2
	srl	$7, $3, 1
	sll	$8, $7, 31
	xor	$1, $1, $8
	slti	$1, $1, 0
	movn	$5, $6, $1
	addiu	$1, $4, 1
	sll	$6, $5, 1
	andi	$7, $7, 85
	sll	$3, $3, 1
	andi	$3, $3, 170
	or	$7, $3, $7
	sll	$8, $7, 2
	lbu	$3, 0($4)
	xor	$4, $6, $2
	srl	$7, $7, 2
	sll	$9, $7, 30
	xor	$5, $5, $9
	slti	$5, $5, 0
	movn	$6, $4, $5
	andi	$4, $8, 192
	or	$4, $4, $7
	srl	$4, $4, 4
	sll	$8, $4, 31
	sll	$5, $4, 30
	sll	$9, $4, 29
	sll	$10, $6, 1
	xor	$11, $10, $2
	sll	$7, $7, 31
	xor	$6, $6, $7
	slti	$6, $6, 0
	movn	$10, $11, $6
	sll	$6, $10, 1
	xor	$7, $6, $2
	sll	$4, $4, 28
	xor	$4, $10, $4
	slti	$4, $4, 0
	movn	$6, $7, $4
	sll	$4, $6, 1
	xor	$7, $4, $2
	xor	$6, $6, $9
	slti	$6, $6, 0
	movn	$4, $7, $6
	sll	$6, $4, 1
	xor	$7, $6, $2
	xor	$4, $4, $5
	slti	$4, $4, 0
	movn	$6, $7, $4
	sll	$5, $6, 1
	xor	$4, $5, $2
	xor	$6, $6, $8
	slti	$6, $6, 0
	movn	$5, $4, $6
	bnez	$3, $BB1_2
	move	 $4, $1
	not	$2, $5
$BB1_4:
	srl	$1, $2, 1
	lui	$3, 21845
	ori	$3, $3, 21845
	and	$1, $1, $3
	sll	$2, $2, 1
	lui	$3, 43690
	ori	$3, $3, 43690
	and	$2, $2, $3
	or	$1, $2, $1
	srl	$2, $1, 2
	lui	$3, 13107
	ori	$3, $3, 13107
	and	$2, $2, $3
	sll	$1, $1, 2
	lui	$3, 52428
	ori	$3, $3, 52428
	and	$1, $1, $3
	or	$1, $1, $2
	lui	$2, 61680
	lui	$3, 3855
	lui	$4, 255
	srl	$5, $1, 4
	ori	$3, $3, 3855
	and	$3, $5, $3
	sll	$1, $1, 4
	ori	$2, $2, 61680
	and	$1, $1, $2
	or	$1, $1, $3
	sll	$2, $1, 24
	srl	$3, $1, 24
	or	$2, $3, $2
	sll	$3, $1, 8
	and	$3, $3, $4
	or	$2, $2, $3
	srl	$1, $1, 8
	andi	$1, $1, 65280
	jr	$ra
	or	$2, $2, $1
	.set	at
	.set	macro
	.set	reorder
	.end	crc32a
$func_end1:
	.size	crc32a, ($func_end1)-crc32a

	.globl	crc32b
	.align	2
	.type	crc32b,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	crc32b
crc32b:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lbu	$3, 0($4)
	beqz	$3, $BB2_4
	addiu	$2, $zero, 0
	addiu	$4, $4, 1
	addiu	$5, $zero, -1
	lui	$1, 60856
	ori	$2, $1, 33568
$BB2_2:
	andi	$1, $3, 255
	xor	$1, $1, $5
	andi	$3, $1, 1
	negu	 $3, $3
	and	$3, $3, $2
	srl	$5, $1, 1
	xor	$5, $3, $5
	ext $6, $5, 1, 1
	addiu	$7, $4, 1
	lbu	$3, 0($4)
	negu	 $4, $6
	and	$4, $4, $2
	srl	$5, $5, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $2
	xor	$1, $1, $5
	srl	$5, $1, 1
	xor	$4, $4, $5
	ext $5, $4, 1, 1
	negu	 $5, $5
	and	$5, $5, $2
	srl	$4, $4, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $2
	xor	$1, $1, $4
	srl	$4, $1, 1
	xor	$4, $5, $4
	ext $5, $4, 1, 1
	negu	 $5, $5
	and	$5, $5, $2
	srl	$4, $4, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $2
	xor	$1, $1, $4
	srl	$4, $1, 1
	xor	$4, $5, $4
	srl	$4, $4, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $2
	xor	$5, $1, $4
	bnez	$3, $BB2_2
	move	 $4, $7
	not	$2, $5
$BB2_4:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	crc32b
$func_end2:
	.size	crc32b, ($func_end2)-crc32b

	.globl	crc32c
	.align	2
	.type	crc32c,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	crc32c
crc32c:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$1, %hi(crc32c.table)
	addiu	$2, $1, %lo(crc32c.table)
	lw	$1, 4($2)
	bnez	$1, $BB3_3
	nop
	addiu	$3, $zero, 0
	lui	$1, 60856
	ori	$5, $1, 33568
	addiu	$6, $zero, 256
$BB3_2:
	ext $1, $3, 1, 1
	negu	 $1, $1
	and	$1, $1, $5
	andi	$7, $3, 1
	negu	 $7, $7
	and	$7, $7, $5
	srl	$8, $3, 1
	xor	$7, $7, $8
	srl	$8, $7, 1
	xor	$1, $1, $8
	ext $8, $1, 1, 1
	addiu	$9, $2, 4
	addiu	$3, $3, 1
	negu	 $8, $8
	and	$8, $8, $5
	srl	$1, $1, 1
	ext $7, $7, 1, 1
	negu	 $7, $7
	and	$7, $7, $5
	xor	$1, $7, $1
	srl	$7, $1, 1
	xor	$7, $8, $7
	ext $8, $7, 1, 1
	negu	 $8, $8
	and	$8, $8, $5
	srl	$7, $7, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $5
	xor	$1, $1, $7
	srl	$7, $1, 1
	xor	$7, $8, $7
	ext $8, $7, 1, 1
	negu	 $8, $8
	and	$8, $8, $5
	srl	$7, $7, 1
	ext $1, $1, 1, 1
	negu	 $1, $1
	and	$1, $1, $5
	xor	$1, $1, $7
	srl	$1, $1, 1
	xor	$1, $8, $1
	sw	$1, 0($2)
	bne	$3, $6, $BB3_2
	move	 $2, $9
$BB3_3:
	lbu	$3, 0($4)
	beqz	$3, $BB3_7
	addiu	$2, $zero, 0
	addiu	$2, $4, 1
	addiu	$4, $zero, -1
	lui	$1, %hi(crc32c.table)
	addiu	$5, $1, %lo(crc32c.table)
$BB3_5:
	xor	$1, $3, $4
	andi	$1, $1, 255
	sll	$1, $1, 2
	addu	$1, $5, $1
	lw	$1, 0($1)
	lbu	$3, 0($2)
	addiu	$2, $2, 1
	srl	$4, $4, 8
	bnez	$3, $BB3_5
	xor	$4, $1, $4
	not	$2, $4
$BB3_7:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	crc32c
$func_end3:
	.size	crc32c, ($func_end3)-crc32c

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,64,$ra
	.mask 	0x803f0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -64
	sw	$ra, 60($sp)
	sw	$21, 56($sp)
	sw	$20, 52($sp)
	sw	$19, 48($sp)
	sw	$18, 44($sp)
	sw	$17, 40($sp)
	sw	$16, 36($sp)
	addiu	$19, $zero, 97
	addiu	$20, $zero, 10
	addiu	$16, $sp, 16
	addiu	$21, $zero, 197
$BB4_1:
	andi	$1, $19, 255
	sll	$2, $1, 8
	or	$2, $2, $1
	sll	$3, $1, 16
	sb	$19, 34($sp)
	sh	$2, 32($sp)
	or	$2, $3, $2
	sll	$1, $1, 24
	or	$1, $1, $2
	sw	$1, 28($sp)
	sw	$1, 24($sp)
	sw	$1, 20($sp)
	sw	$1, 16($sp)
	sb	$20, 35($sp)
	jal	crc32a
	move	 $4, $16
	move	 $17, $2
	jal	crc32b
	move	 $4, $16
	move	 $18, $2
	jal	crc32c
	move	 $4, $16
	addiu	$19, $19, 1
	bne	$19, $21, $BB4_1
	nop
	or	$1, $18, $17
	or	$1, $1, $2
	sltu	$2, $zero, $1
	lw	$16, 36($sp)
	lw	$17, 40($sp)
	lw	$18, 44($sp)
	lw	$19, 48($sp)
	lw	$20, 52($sp)
	lw	$21, 56($sp)
	lw	$ra, 60($sp)
	jr	$ra
	addiu	$sp, $sp, 64
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end4:
	.size	main, ($func_end4)-main

	.type	crc32c.table,@object
	.local	crc32c.table
	.comm	crc32c.table,1024,4

	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
