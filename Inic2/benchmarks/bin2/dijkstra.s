	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/dijkstra.c"
	.text
	.globl	add_edge
	.align	2
	.type	add_edge,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	add_edge
add_edge:
	.frame	$sp,48,$ra
	.mask 	0x801f0000,-12
	.fmask	0x00300000,-8
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -48
	sdc1	$f20, 40($sp)
	sw	$ra, 36($sp)
	sw	$20, 32($sp)
	sw	$19, 28($sp)
	sw	$18, 24($sp)
	sw	$17, 20($sp)
	sw	$16, 16($sp)
	move	 $17, $5
	move	 $16, $4
	mtc1	$7, $f20
	mthc1	$6, $f20
	lui	$18, %hi(e_next)
	lw	$19, %lo(e_next)($18)
	lui	$20, %hi(edge_root)
	lw	$1, %lo(edge_root)($20)
	bne	$19, $1, $BB0_2
	nop
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($20)
	sw	$19, 184($2)
	addiu	$19, $2, 180
	sw	$19, %lo(e_next)($18)
$BB0_2:
	addiu	$1, $19, -12
	sw	$1, %lo(e_next)($18)
	sw	$17, -12($19)
	lw	$1, %lo(e_next)($18)
	trunc.w.d	$f0, $f20
	swc1	$f0, 8($1)
	lw	$2, 0($16)
	sw	$2, 4($1)
	lw	$1, %lo(e_next)($18)
	sw	$1, 0($16)
	lw	$16, 16($sp)
	lw	$17, 20($sp)
	lw	$18, 24($sp)
	lw	$19, 28($sp)
	lw	$20, 32($sp)
	lw	$ra, 36($sp)
	ldc1	$f20, 40($sp)
	jr	$ra
	addiu	$sp, $sp, 48
	.set	at
	.set	macro
	.set	reorder
	.end	add_edge
$func_end0:
	.size	add_edge, ($func_end0)-add_edge

	.globl	free_edges
	.align	2
	.type	free_edges,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	free_edges
free_edges:
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
	lui	$16, %hi(edge_root)
	lw	$4, %lo(edge_root)($16)
	beqz	$4, $BB1_3
	nop
	lui	$17, %hi(e_next)
$BB1_2:
	lw	$1, 184($4)
	jal	free
	sw	$1, %lo(e_next)($17)
	lw	$4, %lo(e_next)($17)
	bnez	$4, $BB1_2
	sw	$4, %lo(edge_root)($16)
$BB1_3:
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$ra, 28($sp)
	jr	$ra
	addiu	$sp, $sp, 32
	.set	at
	.set	macro
	.set	reorder
	.end	free_edges
$func_end1:
	.size	free_edges, ($func_end1)-free_edges

	.globl	set_dist
	.align	2
	.type	set_dist,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	set_dist
set_dist:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	mtc1	$7, $f0
	mthc1	$6, $f0
	lw	$1, 4($4)
	beqz	$1, $BB2_2
	nop
	ldc1	$f2, 8($4)
	c.ole.d	$f2, $f0
	bc1t	 $BB2_12
	nop
$BB2_2:
	sdc1	$f0, 8($4)
	sw	$5, 4($4)
	lw	$2, 24($4)
	bnez	$2, $BB2_4
	nop
	lui	$1, %hi(heap_len)
	lw	$2, %lo(heap_len)($1)
	addiu	$2, $2, 1
	sw	$2, %lo(heap_len)($1)
$BB2_4:
	slti	$1, $2, 2
	bnez	$1, $BB2_9
	nop
	lui	$5, %hi(heap)
$BB2_6:
	srl	$1, $2, 31
	addu	$1, $2, $1
	sra	$3, $1, 1
	sll	$1, $3, 2
	lw	$6, %lo(heap)($5)
	addu	$1, $6, $1
	lw	$7, 0($1)
	ldc1	$f2, 8($7)
	c.ule.d	$f2, $f0
	bc1t	 $BB2_10
	nop
	sll	$1, $2, 2
	addu	$1, $6, $1
	sw	$7, 0($1)
	sw	$2, 24($7)
	slti	$1, $2, 4
	beqz	$1, $BB2_6
	move	 $2, $3
	j	$BB2_11
	nop
$BB2_9:
	j	$BB2_11
	move	 $3, $2
$BB2_10:
	move	 $3, $2
$BB2_11:
	lui	$1, %hi(heap)
	lw	$1, %lo(heap)($1)
	sll	$2, $3, 2
	addu	$1, $1, $2
	sw	$4, 0($1)
	sw	$3, 24($4)
$BB2_12:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	set_dist
$func_end2:
	.size	set_dist, ($func_end2)-set_dist

	.globl	pop_queue
	.align	2
	.type	pop_queue,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	pop_queue
pop_queue:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$5, %hi(heap_len)
	lw	$3, %lo(heap_len)($5)
	beqz	$3, $BB3_14
	addiu	$2, $zero, 0
	lui	$4, %hi(heap)
	lw	$6, %lo(heap)($4)
	lw	$2, 4($6)
	addiu	$8, $3, -1
	sw	$8, %lo(heap_len)($5)
	sll	$1, $3, 2
	addu	$1, $6, $1
	lw	$3, 0($1)
	slti	$1, $8, 2
	bnez	$1, $BB3_13
	addiu	$5, $zero, 1
	addiu	$7, $zero, 1
	lui	$6, %hi(heap_len)
$BB3_3:
	sll	$5, $7, 1
	slt	$1, $8, $5
	bnez	$1, $BB3_10
	nop
	slt	$1, $5, $8
	beqz	$1, $BB3_7
	lw	$8, %lo(heap)($4)
	sll	$1, $5, 2
	addu	$1, $8, $1
	lw	$1, 0($1)
	ldc1	$f0, 8($1)
	ori	$9, $5, 1
	sll	$1, $9, 2
	addu	$1, $8, $1
	lw	$1, 0($1)
	ldc1	$f2, 8($1)
	c.ule.d	$f0, $f2
	bc1t	 $BB3_7
	nop
	move	 $5, $9
$BB3_7:
	sll	$1, $5, 2
	addu	$1, $8, $1
	lw	$9, 0($1)
	ldc1	$f0, 8($9)
	ldc1	$f2, 8($3)
	c.ult.d	$f0, $f2
	bc1f	 $BB3_11
	nop
	sll	$1, $7, 2
	addu	$1, $8, $1
	sw	$9, 0($1)
	sw	$7, 24($9)
	lw	$8, %lo(heap_len)($6)
	slt	$1, $5, $8
	bnez	$1, $BB3_3
	move	 $7, $5
	j	$BB3_12
	nop
$BB3_10:
	j	$BB3_12
	move	 $5, $7
$BB3_11:
	move	 $5, $7
$BB3_12:
	lui	$1, %hi(heap)
	lw	$6, %lo(heap)($1)
$BB3_13:
	sll	$1, $5, 2
	addu	$1, $6, $1
	sw	$3, 0($1)
	sw	$5, 24($3)
$BB3_14:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	pop_queue
$func_end3:
	.size	pop_queue, ($func_end3)-pop_queue

	.globl	calc_all
	.align	2
	.type	calc_all,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	calc_all
calc_all:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lw	$1, 4($4)
	beqz	$1, $BB4_2
	nop
	ldc1	$f0, 8($4)
	mtc1	$zero, $f2
	mthc1	$zero, $f2
	c.ole.d	$f0, $f2
	bc1t	 $BB4_12
	nop
$BB4_2:
	sw	$zero, 12($4)
	sw	$zero, 8($4)
	sw	$4, 4($4)
	lw	$2, 24($4)
	bnez	$2, $BB4_4
	nop
	lui	$1, %hi(heap_len)
	lw	$2, %lo(heap_len)($1)
	addiu	$2, $2, 1
	sw	$2, %lo(heap_len)($1)
$BB4_4:
	slti	$1, $2, 2
	bnez	$1, $BB4_9
	nop
	lui	$5, %hi(heap)
$BB4_6:
	srl	$1, $2, 31
	addu	$1, $2, $1
	sra	$3, $1, 1
	sll	$1, $3, 2
	lw	$6, %lo(heap)($5)
	addu	$1, $6, $1
	lw	$7, 0($1)
	mtc1	$zero, $f0
	mthc1	$zero, $f0
	ldc1	$f2, 8($7)
	c.ule.d	$f2, $f0
	bc1t	 $BB4_10
	nop
	sll	$1, $2, 2
	addu	$1, $6, $1
	sw	$7, 0($1)
	sw	$2, 24($7)
	slti	$1, $2, 4
	beqz	$1, $BB4_6
	move	 $2, $3
	j	$BB4_11
	nop
$BB4_9:
	j	$BB4_11
	move	 $3, $2
$BB4_10:
	move	 $3, $2
$BB4_11:
	lui	$1, %hi(heap)
	lw	$1, %lo(heap)($1)
	sll	$2, $3, 2
	addu	$1, $1, $2
	sw	$4, 0($1)
	sw	$3, 24($4)
$BB4_12:
	lui	$2, %hi(heap_len)
	lw	$5, %lo(heap_len)($2)
	beqz	$5, $BB4_40
	nop
	lui	$3, %hi(heap)
$BB4_14:
	lw	$7, %lo(heap)($3)
	lw	$4, 4($7)
	addiu	$8, $5, -1
	sw	$8, %lo(heap_len)($2)
	sll	$1, $5, 2
	addu	$1, $7, $1
	lw	$5, 0($1)
	slti	$1, $8, 2
	bnez	$1, $BB4_26
	addiu	$6, $zero, 1
	addiu	$7, $zero, 1
$BB4_16:
	sll	$6, $7, 1
	slt	$1, $8, $6
	bnez	$1, $BB4_23
	nop
	slt	$1, $6, $8
	beqz	$1, $BB4_20
	lw	$8, %lo(heap)($3)
	sll	$1, $6, 2
	addu	$1, $8, $1
	lw	$1, 0($1)
	ldc1	$f0, 8($1)
	ori	$9, $6, 1
	sll	$1, $9, 2
	addu	$1, $8, $1
	lw	$1, 0($1)
	ldc1	$f2, 8($1)
	c.ule.d	$f0, $f2
	bc1t	 $BB4_20
	nop
	move	 $6, $9
$BB4_20:
	sll	$1, $6, 2
	addu	$1, $8, $1
	lw	$9, 0($1)
	ldc1	$f0, 8($9)
	ldc1	$f2, 8($5)
	c.ult.d	$f0, $f2
	bc1f	 $BB4_24
	nop
	sll	$1, $7, 2
	addu	$1, $8, $1
	sw	$9, 0($1)
	sw	$7, 24($9)
	lw	$8, %lo(heap_len)($2)
	slt	$1, $6, $8
	bnez	$1, $BB4_16
	move	 $7, $6
	j	$BB4_25
	nop
$BB4_23:
	j	$BB4_25
	move	 $6, $7
$BB4_24:
	move	 $6, $7
$BB4_25:
	lw	$7, %lo(heap)($3)
$BB4_26:
	sll	$1, $6, 2
	addu	$1, $7, $1
	sw	$5, 0($1)
	beqz	$4, $BB4_40
	sw	$6, 24($5)
	lw	$5, 0($4)
	beqz	$5, $BB4_39
	nop
$BB4_28:
	ldc1	$f0, 8($4)
	lw	$1, 8($5)
	mtc1	$1, $f2
	cvt.d.w	$f2, $f2
	lw	$6, 0($5)
	lw	$1, 4($6)
	beqz	$1, $BB4_30
	add.d	$f0, $f0, $f2
	ldc1	$f2, 8($6)
	c.ole.d	$f2, $f0
	bc1t	 $BB4_38
	nop
$BB4_30:
	sdc1	$f0, 8($6)
	sw	$4, 4($6)
	lw	$7, 24($6)
	bnez	$7, $BB4_32
	nop
	lw	$1, %lo(heap_len)($2)
	addiu	$7, $1, 1
	sw	$7, %lo(heap_len)($2)
$BB4_32:
	slti	$1, $7, 2
	bnez	$1, $BB4_37
	move	 $8, $7
$BB4_33:
	srl	$1, $7, 31
	addu	$1, $7, $1
	sra	$8, $1, 1
	sll	$1, $8, 2
	lw	$9, %lo(heap)($3)
	addu	$1, $9, $1
	lw	$10, 0($1)
	ldc1	$f2, 8($10)
	c.ule.d	$f2, $f0
	bc1t	 $BB4_36
	nop
	sll	$1, $7, 2
	addu	$1, $9, $1
	sw	$10, 0($1)
	sw	$7, 24($10)
	slti	$1, $7, 4
	beqz	$1, $BB4_33
	move	 $7, $8
	j	$BB4_37
	nop
$BB4_36:
	move	 $8, $7
$BB4_37:
	lw	$1, %lo(heap)($3)
	sll	$7, $8, 2
	addu	$1, $1, $7
	sw	$6, 0($1)
	sw	$8, 24($6)
$BB4_38:
	lw	$5, 4($5)
	bnez	$5, $BB4_28
	nop
$BB4_39:
	lw	$5, %lo(heap_len)($2)
	bnez	$5, $BB4_14
	nop
$BB4_40:
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	calc_all
$func_end4:
	.size	calc_all, ($func_end4)-calc_all

	.globl	show_path
	.align	2
	.type	show_path,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	show_path
show_path:
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
	lw	$4, 4($16)
	beq	$4, $16, $BB5_3
	nop
	beqz	$4, $BB5_4
	nop
	jal	show_path
	nop
	ldc1	$f0, 8($16)
	addiu	$5, $16, 16
	lui	$1, %hi($.str.2)
	addiu	$4, $1, %lo($.str.2)
	mfhc1	$6, $f0
	jal	printf
	mfc1	$7, $f0
	lw	$16, 16($sp)
	lw	$ra, 20($sp)
	jr	$ra
	addiu	$sp, $sp, 24
$BB5_3:
	addiu	$5, $16, 16
	lui	$1, %hi($.str)
	jal	printf
	addiu	$4, $1, %lo($.str)
	j	$BB5_5
	nop
$BB5_4:
	addiu	$5, $16, 16
	lui	$1, %hi($.str.1)
	jal	printf
	addiu	$4, $1, %lo($.str.1)
$BB5_5:
	lw	$16, 16($sp)
	lw	$ra, 20($sp)
	jr	$ra
	addiu	$sp, $sp, 24
	.set	at
	.set	macro
	.set	reorder
	.end	show_path
$func_end5:
	.size	show_path, ($func_end5)-show_path

	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,56,$ra
	.mask 	0x80ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -56
	sw	$ra, 52($sp)
	sw	$23, 48($sp)
	sw	$22, 44($sp)
	sw	$21, 40($sp)
	sw	$20, 36($sp)
	sw	$19, 32($sp)
	sw	$18, 28($sp)
	sw	$17, 24($sp)
	sw	$16, 20($sp)
	addiu	$4, $zero, 32
	jal	calloc
	addiu	$5, $zero, 6
	move	 $16, $2
	addiu	$1, $zero, 97
	sb	$1, 16($16)
	addiu	$1, $zero, 98
	sb	$1, 48($16)
	addiu	$1, $zero, 99
	sb	$1, 80($16)
	addiu	$1, $zero, 100
	sb	$1, 112($16)
	addiu	$1, $zero, 101
	sb	$1, 144($16)
	lui	$17, %hi(edge_root)
	lui	$20, %hi(e_next)
	addiu	$1, $zero, 102
	sb	$1, 176($16)
	lw	$18, %lo(e_next)($20)
	lw	$1, %lo(edge_root)($17)
	bne	$18, $1, $BB6_2
	addiu	$19, $16, 32
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($17)
	sw	$18, 184($2)
	addiu	$18, $2, 180
	sw	$18, %lo(e_next)($20)
$BB6_2:
	addiu	$1, $18, -12
	sw	$1, %lo(e_next)($20)
	sw	$19, -12($18)
	lw	$1, %lo(e_next)($20)
	addiu	$2, $zero, 7
	sw	$2, 8($1)
	addiu	$18, $16, 64
	sw	$zero, 4($1)
	lw	$21, %lo(e_next)($20)
	sw	$21, 0($16)
	lw	$1, %lo(edge_root)($17)
	bne	$21, $1, $BB6_4
	move	 $2, $21
	jal	malloc
	addiu	$4, $zero, 192
	lui	$1, %hi(edge_root)
	sw	$2, %lo(edge_root)($1)
	sw	$21, 184($2)
	addiu	$2, $2, 180
	lui	$1, %hi(e_next)
	sw	$2, %lo(e_next)($1)
$BB6_4:
	addiu	$1, $2, -12
	lui	$20, %hi(e_next)
	sw	$1, %lo(e_next)($20)
	sw	$18, -12($2)
	lw	$1, %lo(e_next)($20)
	addiu	$2, $zero, 9
	sw	$2, 8($1)
	addiu	$17, $16, 160
	lui	$22, %hi(edge_root)
	sw	$21, 4($1)
	lw	$21, %lo(e_next)($20)
	sw	$21, 0($16)
	lw	$1, %lo(edge_root)($22)
	bne	$21, $1, $BB6_6
	move	 $2, $21
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($22)
	sw	$21, 184($2)
	addiu	$2, $2, 180
	sw	$2, %lo(e_next)($20)
$BB6_6:
	addiu	$1, $2, -12
	sw	$1, %lo(e_next)($20)
	sw	$17, -12($2)
	lw	$1, %lo(e_next)($20)
	addiu	$2, $zero, 14
	sw	$2, 8($1)
	sw	$21, 4($1)
	lw	$20, %lo(e_next)($20)
	sw	$20, 0($16)
	lw	$1, %lo(edge_root)($22)
	bne	$20, $1, $BB6_8
	nop
	jal	malloc
	addiu	$4, $zero, 192
	lui	$1, %hi(edge_root)
	sw	$2, %lo(edge_root)($1)
	sw	$20, 184($2)
	addiu	$20, $2, 180
	lui	$1, %hi(e_next)
	sw	$20, %lo(e_next)($1)
$BB6_8:
	addiu	$1, $20, -12
	lui	$21, %hi(e_next)
	sw	$1, %lo(e_next)($21)
	sw	$18, -12($20)
	lw	$1, %lo(e_next)($21)
	addiu	$2, $zero, 10
	sw	$2, 8($1)
	addiu	$20, $16, 96
	lui	$22, %hi(edge_root)
	sw	$zero, 4($1)
	lw	$23, %lo(e_next)($21)
	sw	$23, 32($16)
	lw	$1, %lo(edge_root)($22)
	bne	$23, $1, $BB6_10
	move	 $2, $23
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($22)
	sw	$23, 184($2)
	addiu	$2, $2, 180
	sw	$2, %lo(e_next)($21)
$BB6_10:
	addiu	$1, $2, -12
	sw	$1, %lo(e_next)($21)
	sw	$20, -12($2)
	lw	$1, %lo(e_next)($21)
	addiu	$2, $zero, 15
	sw	$2, 8($1)
	sw	$23, 4($1)
	lw	$21, %lo(e_next)($21)
	sw	$21, 0($19)
	lw	$1, %lo(edge_root)($22)
	bne	$21, $1, $BB6_12
	nop
	jal	malloc
	addiu	$4, $zero, 192
	lui	$1, %hi(edge_root)
	sw	$2, %lo(edge_root)($1)
	sw	$21, 184($2)
	addiu	$21, $2, 180
	lui	$1, %hi(e_next)
	sw	$21, %lo(e_next)($1)
$BB6_12:
	addiu	$1, $21, -12
	lui	$19, %hi(e_next)
	sw	$1, %lo(e_next)($19)
	sw	$20, -12($21)
	lw	$1, %lo(e_next)($19)
	addiu	$2, $zero, 11
	sw	$2, 8($1)
	lui	$21, %hi(edge_root)
	sw	$zero, 4($1)
	lw	$22, %lo(e_next)($19)
	sw	$22, 0($18)
	lw	$1, %lo(edge_root)($21)
	bne	$22, $1, $BB6_14
	move	 $2, $22
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($21)
	sw	$22, 184($2)
	addiu	$2, $2, 180
	sw	$2, %lo(e_next)($19)
$BB6_14:
	addiu	$1, $2, -12
	sw	$1, %lo(e_next)($19)
	sw	$17, -12($2)
	lw	$1, %lo(e_next)($19)
	addiu	$2, $zero, 2
	sw	$2, 8($1)
	sw	$22, 4($1)
	lw	$22, %lo(e_next)($19)
	sw	$22, 64($16)
	lw	$1, %lo(edge_root)($21)
	bne	$22, $1, $BB6_16
	addiu	$18, $16, 128
	jal	malloc
	addiu	$4, $zero, 192
	lui	$1, %hi(edge_root)
	sw	$2, %lo(edge_root)($1)
	sw	$22, 184($2)
	addiu	$22, $2, 180
	lui	$1, %hi(e_next)
	sw	$22, %lo(e_next)($1)
$BB6_16:
	addiu	$1, $22, -12
	lui	$19, %hi(e_next)
	sw	$1, %lo(e_next)($19)
	sw	$18, -12($22)
	lw	$1, %lo(e_next)($19)
	addiu	$2, $zero, 6
	sw	$2, 8($1)
	lui	$18, %hi(edge_root)
	sw	$zero, 4($1)
	lw	$21, %lo(e_next)($19)
	sw	$21, 0($20)
	lw	$1, %lo(edge_root)($18)
	bne	$21, $1, $BB6_18
	nop
	jal	malloc
	addiu	$4, $zero, 192
	sw	$2, %lo(edge_root)($18)
	sw	$21, 184($2)
	addiu	$21, $2, 180
	sw	$21, %lo(e_next)($19)
$BB6_18:
	addiu	$1, $21, -12
	sw	$1, %lo(e_next)($19)
	sw	$17, -12($21)
	lw	$1, %lo(e_next)($19)
	addiu	$2, $zero, 9
	sw	$2, 8($1)
	sw	$zero, 4($1)
	lw	$1, %lo(e_next)($19)
	sw	$1, 128($16)
	addiu	$4, $zero, 4
	jal	calloc
	addiu	$5, $zero, 7
	lui	$1, %hi(heap_len)
	lui	$17, %hi(heap)
	sw	$2, %lo(heap)($17)
	sw	$zero, %lo(heap_len)($1)
	jal	calc_all
	move	 $4, $16
	jal	show_path
	move	 $4, $16
	jal	putchar
	addiu	$4, $zero, 10
	jal	show_path
	addiu	$4, $16, 32
	jal	putchar
	addiu	$4, $zero, 10
	jal	show_path
	addiu	$4, $16, 64
	jal	putchar
	addiu	$4, $zero, 10
	jal	show_path
	addiu	$4, $16, 96
	jal	putchar
	addiu	$4, $zero, 10
	jal	show_path
	addiu	$4, $16, 128
	jal	putchar
	addiu	$4, $zero, 10
	jal	show_path
	addiu	$4, $16, 160
	jal	putchar
	addiu	$4, $zero, 10
	lw	$4, %lo(edge_root)($18)
	beqz	$4, $BB6_21
	nop
	lui	$18, %hi(e_next)
	lui	$19, %hi(edge_root)
$BB6_20:
	lw	$1, 184($4)
	jal	free
	sw	$1, %lo(e_next)($18)
	lw	$4, %lo(e_next)($18)
	bnez	$4, $BB6_20
	sw	$4, %lo(edge_root)($19)
$BB6_21:
	lw	$4, %lo(heap)($17)
	jal	free
	nop
	jal	free
	move	 $4, $16
	addiu	$2, $zero, 0
	lw	$16, 20($sp)
	lw	$17, 24($sp)
	lw	$18, 28($sp)
	lw	$19, 32($sp)
	lw	$20, 36($sp)
	lw	$21, 40($sp)
	lw	$22, 44($sp)
	lw	$23, 48($sp)
	lw	$ra, 52($sp)
	jr	$ra
	addiu	$sp, $sp, 56
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end6:
	.size	main, ($func_end6)-main

	.type	edge_root,@object
	.bss
	.globl	edge_root
	.align	2
edge_root:
	.4byte	0
	.size	edge_root, 4

	.type	e_next,@object
	.globl	e_next
	.align	2
e_next:
	.4byte	0
	.size	e_next, 4

	.type	heap_len,@object
	.comm	heap_len,4,4
	.type	heap,@object
	.comm	heap,4,4
	.type	$.str,@object
	.section	.rodata.str1.1,"aMS",@progbits,1
$.str:
	.asciz	"%s"
	.size	$.str, 3

	.type	$.str.1,@object
$.str.1:
	.asciz	"%s(unreached)"
	.size	$.str.1, 14

	.type	$.str.2,@object
$.str.2:
	.asciz	"-> %s(%g) "
	.size	$.str.2, 11


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
