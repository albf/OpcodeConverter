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
	.frame	$fp,24,$ra
	.mask 	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$fp, 20($sp)
	move	 $fp, $sp
	lw	$1, 40($fp)
	sw	$4, 16($fp)
	sw	$5, 12($fp)
	sw	$6, 8($fp)
	sw	$7, 4($fp)
	sw	$1, 0($fp)
	lw	$1, 16($fp)
	sll	$1, $1, 2
	lw	$4, 4($fp)
	addu	$1, $4, $1
	lw	$1, 0($1)
	lw	$5, 12($fp)
	lw	$6, 8($fp)
	addu	$1, $1, $6
	sll	$5, $5, 2
	addu	$4, $4, $5
	lw	$4, 0($4)
	slt	$1, $1, $4
	beqz	$1, $BB0_3
	nop
	j	$BB0_2
	nop
$BB0_2:
	lw	$1, 12($fp)
	lw	$2, 16($fp)
	sll	$2, $2, 2
	sll	$1, $1, 2
	lw	$3, 4($fp)
	addu	$1, $3, $1
	addu	$2, $3, $2
	lw	$2, 0($2)
	lw	$3, 8($fp)
	addu	$2, $2, $3
	sw	$2, 0($1)
	lw	$1, 12($fp)
	sll	$1, $1, 2
	lw	$2, 0($fp)
	addu	$1, $2, $1
	lw	$2, 16($fp)
	sw	$2, 0($1)
$BB0_3:
	move	 $sp, $fp
	lw	$fp, 20($sp)
	addiu	$sp, $sp, 24
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
	.frame	$fp,24,$ra
	.mask 	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -24
	sw	$fp, 20($sp)
	move	 $fp, $sp
	sw	$4, 16($fp)
	sw	$5, 12($fp)
	sw	$6, 8($fp)
	sw	$7, 4($fp)
	addiu	$4, $zero, 1
	sw	$4, 0($fp)
$BB1_1:
	lw	$1, 0($fp)
	lw	$2, 4($fp)
	slt	$1, $2, $1
	bnez	$1, $BB1_5
	nop
	j	$BB1_3
	nop
$BB1_3:
	lw	$1, 0($fp)
	sll	$1, $1, 2
	lw	$2, 16($fp)
	addu	$1, $2, $1
	lui	$2, 15
	ori	$2, $2, 16960
	sw	$2, 0($1)
	lw	$1, 0($fp)
	sll	$1, $1, 2
	lw	$2, 12($fp)
	addu	$1, $2, $1
	sw	$zero, 0($1)
	lw	$1, 0($fp)
	addiu	$1, $1, 1
	sw	$1, 0($fp)
	j	$BB1_1
	nop
$BB1_5:
	lw	$1, 8($fp)
	sll	$1, $1, 2
	lw	$2, 16($fp)
	addu	$1, $2, $1
	sw	$zero, 0($1)
	move	 $sp, $fp
	lw	$fp, 20($sp)
	addiu	$sp, $sp, 24
	jr	$ra
	nop
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
	.frame	$fp,88,$ra
	.mask 	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -88
	sw	$ra, 84($sp)
	sw	$fp, 80($sp)
	move	 $fp, $sp
	lw	$1, 116($fp)
	lw	$2, 112($fp)
	lw	$3, 108($fp)
	lw	$8, 104($fp)
	sw	$4, 72($fp)
	sw	$5, 68($fp)
	sw	$6, 64($fp)
	sw	$7, 60($fp)
	sw	$8, 56($fp)
	sw	$3, 52($fp)
	sw	$2, 48($fp)
	sw	$1, 44($fp)
	lw	$6, 48($fp)
	lw	$5, 52($fp)
	lw	$4, 56($fp)
	move	 $7, $1
	jal	initialize_single_source
	nop
	addiu	$1, $zero, 1
	sw	$1, 32($fp)
$BB2_1:
	lw	$1, 44($fp)
	addiu	$1, $1, -1
	lw	$2, 32($fp)
	slt	$1, $1, $2
	bnez	$1, $BB2_14
	nop
	j	$BB2_3
	nop
$BB2_3:
	addiu	$1, $zero, 1
	sw	$1, 40($fp)
$BB2_4:
	lw	$1, 40($fp)
	lw	$2, 44($fp)
	slt	$1, $2, $1
	bnez	$1, $BB2_12
	nop
	j	$BB2_6
	nop
$BB2_6:
	lw	$1, 40($fp)
	sll	$1, $1, 2
	lw	$2, 72($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 28($fp)
$BB2_7:
	lw	$1, 28($fp)
	blez	$1, $BB2_10
	nop
	j	$BB2_9
	nop
$BB2_9:
	lw	$1, 28($fp)
	sll	$1, $1, 2
	lw	$2, 68($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 36($fp)
	lw	$2, 28($fp)
	sll	$2, $2, 2
	lw	$3, 60($fp)
	addu	$2, $3, $2
	lw	$6, 0($2)
	lw	$7, 56($fp)
	lw	$4, 40($fp)
	lw	$2, 52($fp)
	move	 $3, $sp
	sw	$2, 16($3)
	move	 $5, $1
	jal	relax
	nop
	lw	$1, 28($fp)
	sll	$1, $1, 2
	lw	$2, 64($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 28($fp)
	j	$BB2_7
	nop
$BB2_10:
	j	$BB2_11
	nop
$BB2_11:
	lw	$1, 40($fp)
	addiu	$1, $1, 1
	sw	$1, 40($fp)
	j	$BB2_4
	nop
$BB2_12:
	j	$BB2_13
	nop
$BB2_13:
	lw	$1, 32($fp)
	addiu	$1, $1, 1
	sw	$1, 32($fp)
	j	$BB2_1
	nop
$BB2_14:
	addiu	$1, $zero, 1
	sw	$1, 40($fp)
$BB2_15:
	lw	$1, 40($fp)
	lw	$2, 44($fp)
	slt	$1, $2, $1
	bnez	$1, $BB2_26
	nop
	j	$BB2_17
	nop
$BB2_17:
	lw	$1, 40($fp)
	sll	$1, $1, 2
	lw	$2, 72($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 28($fp)
$BB2_18:
	lw	$1, 28($fp)
	blez	$1, $BB2_24
	nop
	j	$BB2_20
	nop
$BB2_20:
	lw	$1, 28($fp)
	sll	$1, $1, 2
	lw	$2, 68($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 36($fp)
	lw	$2, 28($fp)
	sll	$2, $2, 2
	lw	$3, 60($fp)
	addu	$2, $3, $2
	lw	$3, 40($fp)
	sll	$1, $1, 2
	lw	$2, 0($2)
	sll	$3, $3, 2
	lw	$4, 56($fp)
	addu	$3, $4, $3
	lw	$3, 0($3)
	addu	$2, $3, $2
	addu	$1, $4, $1
	lw	$1, 0($1)
	slt	$1, $2, $1
	beqz	$1, $BB2_23
	nop
	j	$BB2_22
	nop
$BB2_22:
	sw	$zero, 76($fp)
	j	$BB2_27
	nop
$BB2_23:
	lw	$1, 28($fp)
	sll	$1, $1, 2
	lw	$2, 64($fp)
	addu	$1, $2, $1
	lw	$1, 0($1)
	sw	$1, 28($fp)
	j	$BB2_18
	nop
$BB2_24:
	j	$BB2_25
	nop
$BB2_25:
	lw	$1, 40($fp)
	addiu	$1, $1, 1
	sw	$1, 40($fp)
	j	$BB2_15
	nop
$BB2_26:
	addiu	$1, $zero, 1
	sw	$1, 76($fp)
$BB2_27:
	lw	$2, 76($fp)
	move	 $sp, $fp
	lw	$fp, 80($sp)
	lw	$ra, 84($sp)
	addiu	$sp, $sp, 88
	jr	$ra
	nop
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
	.frame	$fp,912,$ra
	.mask 	0xc0ff0000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -912
	sw	$ra, 908($sp)
	sw	$fp, 904($sp)
	sw	$23, 900($sp)
	sw	$22, 896($sp)
	sw	$21, 892($sp)
	sw	$20, 888($sp)
	sw	$19, 884($sp)
	sw	$18, 880($sp)
	sw	$17, 876($sp)
	sw	$16, 872($sp)
	move	 $fp, $sp
	sw	$zero, 868($fp)
	addiu	$1, $zero, 1
	sw	$1, 788($fp)
	addiu	$2, $zero, 3
	sw	$2, 792($fp)
	addiu	$3, $zero, 6
	sw	$3, 796($fp)
	addiu	$4, $zero, 7
	sw	$4, 800($fp)
	addiu	$5, $zero, 9
	sw	$5, 804($fp)
	addiu	$6, $zero, 12
	sw	$6, 808($fp)
	addiu	$7, $zero, 26
	addiu	$8, $zero, 24
	addiu	$9, $zero, 18
	addiu	$10, $zero, 14
	addiu	$11, $zero, 44
	addiu	$12, $zero, 42
	addiu	$13, $zero, 40
	addiu	$14, $zero, 38
	addiu	$15, $zero, 36
	addiu	$24, $zero, 34
	addiu	$25, $zero, 32
	addiu	$gp, $zero, 30
	addiu	$16, $zero, 28
	addiu	$17, $zero, 20
	addiu	$18, $zero, 5
	addiu	$19, $zero, 4
	addiu	$20, $zero, 2
	addiu	$21, $zero, 10
	addiu	$22, $zero, 8
	addiu	$23, $zero, 19
	sw	$10, 812($fp)
	sw	$9, 816($fp)
	sw	$17, 820($fp)
	addiu	$ra, $zero, 17
	sw	$8, 824($fp)
	addiu	$8, $zero, 16
	sw	$7, 828($fp)
	addiu	$7, $zero, 15
	sw	$16, 832($fp)
	addiu	$16, $zero, 13
	sw	$gp, 836($fp)
	addiu	$gp, $zero, 11
	sw	$25, 840($fp)
	addiu	$25, $zero, -3
	sw	$24, 844($fp)
	addiu	$24, $zero, -2
	sw	$15, 848($fp)
	addiu	$15, $zero, -4
	sw	$14, 852($fp)
	addiu	$14, $zero, 29
	sw	$13, 856($fp)
	addiu	$13, $zero, 27
	sw	$12, 860($fp)
	addiu	$12, $zero, 25
	sw	$11, 864($fp)
	sw	$20, 600($fp)
	sw	$19, 604($fp)
	sw	$2, 608($fp)
	sw	$19, 612($fp)
	sw	$18, 616($fp)
	sw	$20, 620($fp)
	sw	$2, 624($fp)
	sw	$18, 628($fp)
	sw	$1, 632($fp)
	sw	$2, 636($fp)
	sw	$3, 640($fp)
	sw	$4, 644($fp)
	sw	$22, 648($fp)
	sw	$5, 652($fp)
	sw	$21, 656($fp)
	sw	$1, 660($fp)
	sw	$20, 664($fp)
	sw	$5, 668($fp)
	sw	$19, 672($fp)
	sw	$21, 676($fp)
	sw	$20, 680($fp)
	sw	$21, 684($fp)
	sw	$18, 688($fp)
	sw	$19, 692($fp)
	sw	$gp, 696($fp)
	sw	$6, 700($fp)
	sw	$16, 704($fp)
	sw	$7, 708($fp)
	sw	$8, 712($fp)
	sw	$ra, 716($fp)
	addiu	$11, $zero, 23
	sw	$9, 720($fp)
	sw	$23, 724($fp)
	sw	$17, 728($fp)
	sw	$16, 732($fp)
	sw	$10, 736($fp)
	sw	$7, 740($fp)
	sw	$23, 744($fp)
	sw	$gp, 748($fp)
	sw	$6, 752($fp)
	sw	$16, 756($fp)
	sw	$1, 760($fp)
	sw	$18, 764($fp)
	sw	$20, 768($fp)
	addiu	$9, $zero, 22
	sw	$10, 772($fp)
	sw	$16, 776($fp)
	sw	$19, 780($fp)
	sw	$3, 140($fp)
	sw	$4, 144($fp)
	sw	$18, 148($fp)
	sw	$22, 152($fp)
	addiu	$10, $zero, 21
	sw	$15, 156($fp)
	addiu	$15, $zero, 46
	sw	$24, 160($fp)
	addiu	$24, $zero, 45
	sw	$25, 164($fp)
	sw	$5, 168($fp)
	sw	$20, 172($fp)
	sw	$4, 176($fp)
	sw	$19, 180($fp)
	sw	$20, 184($fp)
	sw	$5, 188($fp)
	sw	$1, 192($fp)
	sw	$18, 196($fp)
	sw	$2, 200($fp)
	sw	$19, 204($fp)
	sw	$5, 208($fp)
	sw	$3, 212($fp)
	addiu	$25, $zero, 43
	sw	$6, 216($fp)
	sw	$1, 220($fp)
	sw	$5, 224($fp)
	sw	$20, 228($fp)
	sw	$1, 232($fp)
	sw	$19, 236($fp)
	sw	$20, 240($fp)
	sw	$2, 244($fp)
	sw	$5, 248($fp)
	sw	$20, 252($fp)
	sw	$4, 256($fp)
	sw	$3, 260($fp)
	sw	$4, 264($fp)
	sw	$18, 268($fp)
	sw	$22, 272($fp)
	sw	$19, 276($fp)
	sw	$20, 280($fp)
	addiu	$6, $zero, 41
	sw	$2, 284($fp)
	addiu	$2, $zero, 39
	sw	$5, 288($fp)
	sw	$20, 292($fp)
	sw	$4, 296($fp)
	addiu	$5, $zero, 37
	sw	$3, 300($fp)
	addiu	$3, $zero, 35
	sw	$4, 304($fp)
	sw	$18, 308($fp)
	sw	$22, 312($fp)
	sw	$19, 316($fp)
	sw	$20, 320($fp)
	addiu	$4, $zero, 33
	sw	$20, 412($fp)
	sw	$zero, 416($fp)
	addiu	$20, $zero, 31
	sw	$19, 420($fp)
	addiu	$19, $fp, 784
	sw	$18, 424($fp)
	sw	$zero, 428($fp)
	sw	$zero, 432($fp)
	addiu	$18, $fp, 596
	sw	$22, 436($fp)
	sw	$zero, 440($fp)
	addiu	$22, $fp, 408
	sw	$21, 444($fp)
	addiu	$21, $fp, 136
	sw	$gp, 448($fp)
	sw	$zero, 452($fp)
	addiu	$gp, $fp, 52
	sw	$16, 456($fp)
	sw	$zero, 460($fp)
	addiu	$16, $fp, 324
	sw	$7, 464($fp)
	sw	$8, 468($fp)
	sw	$ra, 472($fp)
	sw	$zero, 476($fp)
	sw	$23, 480($fp)
	sw	$zero, 484($fp)
	sw	$10, 488($fp)
	sw	$9, 492($fp)
	sw	$11, 496($fp)
	sw	$zero, 500($fp)
	sw	$12, 504($fp)
	sw	$zero, 508($fp)
	sw	$13, 512($fp)
	sw	$zero, 516($fp)
	sw	$14, 520($fp)
	sw	$zero, 524($fp)
	sw	$20, 528($fp)
	sw	$zero, 532($fp)
	sw	$4, 536($fp)
	sw	$zero, 540($fp)
	sw	$3, 544($fp)
	sw	$zero, 548($fp)
	sw	$5, 552($fp)
	sw	$zero, 556($fp)
	sw	$2, 560($fp)
	sw	$zero, 564($fp)
	sw	$6, 568($fp)
	sw	$zero, 572($fp)
	sw	$25, 576($fp)
	sw	$zero, 580($fp)
	sw	$24, 584($fp)
	sw	$15, 588($fp)
	sw	$zero, 592($fp)
	sw	$1, 48($fp)
	move	 $2, $sp
	sw	$17, 28($2)
	sw	$1, 24($2)
	sw	$16, 20($2)
	sw	$gp, 16($2)
	move	 $4, $19
	move	 $5, $18
	move	 $6, $22
	move	 $7, $21
	sw	$1, 32($fp)
	jal	bellman_ford
	nop
	sw	$2, 40($fp)
	sw	$zero, 36($fp)
	lw	$1, 32($fp)
	sw	$1, 44($fp)
$BB3_1:
	lw	$1, 44($fp)
	slti	$1, $1, 6
	beqz	$1, $BB3_5
	nop
	j	$BB3_3
	nop
$BB3_3:
	lw	$1, 44($fp)
	sll	$1, $1, 2
	addiu	$2, $fp, 324
	addu	$2, $2, $1
	lw	$2, 0($2)
	addiu	$3, $fp, 52
	addu	$1, $3, $1
	lw	$1, 0($1)
	lw	$3, 36($fp)
	addu	$1, $1, $2
	addu	$1, $3, $1
	sw	$1, 36($fp)
	lw	$1, 44($fp)
	addiu	$1, $1, 1
	sw	$1, 44($fp)
	j	$BB3_1
	nop
$BB3_5:
	lw	$2, 36($fp)
	move	 $sp, $fp
	lw	$16, 872($sp)
	lw	$17, 876($sp)
	lw	$18, 880($sp)
	lw	$19, 884($sp)
	lw	$20, 888($sp)
	lw	$21, 892($sp)
	lw	$22, 896($sp)
	lw	$23, 900($sp)
	lw	$fp, 904($sp)
	lw	$ra, 908($sp)
	addiu	$sp, $sp, 912
	jr	$ra
	nop
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end3:
	.size	main, ($func_end3)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
