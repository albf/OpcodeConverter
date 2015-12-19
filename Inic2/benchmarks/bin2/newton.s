	.text
	.abicalls
	.option	pic0
	.section	.mdebug.abi32,"",@progbits
	.nan	legacy
	.set	mips32r2
	.file	"src/newton.c"
	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
$CPI0_0:
	.8byte	-4604705439004963635
$CPI0_1:
	.8byte	-4608983858650965606
$CPI0_2:
	.8byte	-4598062629554592154
	.text
	.globl	func
	.align	2
	.type	func,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	func
func:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$1, %hi($CPI0_0)
	ldc1	$f0, %lo($CPI0_0)($1)
	cvt.d.s	$f2, $f12
	add.d	$f0, $f2, $f0
	lui	$1, %hi($CPI0_1)
	ldc1	$f4, %lo($CPI0_1)($1)
	add.d	$f4, $f2, $f4
	lui	$1, %hi($CPI0_2)
	ldc1	$f6, %lo($CPI0_2)($1)
	mul.d	$f0, $f4, $f0
	add.d	$f2, $f2, $f6
	mul.d	$f0, $f2, $f0
	jr	$ra
	cvt.s.d	$f0, $f0
	.set	at
	.set	macro
	.set	reorder
	.end	func
$func_end0:
	.size	func, ($func_end0)-func

	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
$CPI1_0:
	.8byte	-4597837449573223629
$CPI1_1:
	.8byte	4633359591634108416
$CPI1_2:
	.8byte	4613937818241073152
	.text
	.globl	deriv
	.align	2
	.type	deriv,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	deriv
deriv:
	.frame	$sp,0,$ra
	.mask 	0x00000000,0
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	.set	noat
	lui	$1, %hi($CPI1_0)
	ldc1	$f0, %lo($CPI1_0)($1)
	lui	$1, %hi($CPI1_1)
	ldc1	$f2, %lo($CPI1_1)($1)
	cvt.d.s	$f4, $f12
	madd.d	$f0, $f2, $f4, $f0
	mul.s	$f2, $f12, $f12
	lui	$1, %hi($CPI1_2)
	ldc1	$f4, %lo($CPI1_2)($1)
	cvt.d.s	$f2, $f2
	add.d	$f0, $f2, $f0
	mul.d	$f0, $f0, $f4
	jr	$ra
	cvt.s.d	$f0, $f0
	.set	at
	.set	macro
	.set	reorder
	.end	deriv
$func_end1:
	.size	deriv, ($func_end1)-deriv

	.section	.rodata.cst8,"aM",@progbits,8
	.align	3
$CPI2_0:
	.8byte	-4604705439004963635
$CPI2_1:
	.8byte	-4608983858650965606
$CPI2_2:
	.8byte	-4597837449573223629
$CPI2_3:
	.8byte	4633359591634108416
$CPI2_4:
	.8byte	-4598062629554592154
$CPI2_5:
	.8byte	-4609434218613702656
	.text
	.globl	main
	.align	2
	.type	main,@function
	.set	nomicromips
	.set	nomips16
	.set	mips32r2
	.ent	main
main:
	.frame	$sp,16,$ra
	.mask 	0x00000000,0
	.fmask	0x00f00000,-8
	.set	noreorder
	.set	nomacro
	.set	noat
	addiu	$sp, $sp, -16
	sdc1	$f22, 8($sp)
	sdc1	$f20, 0($sp)
	addiu	$2, $zero, 100
	mtc1	$zero, $f0
	lui	$1, %hi($CPI2_0)
	lui	$3, %hi($CPI2_1)
	ldc1	$f2, %lo($CPI2_1)($3)
	ldc1	$f4, %lo($CPI2_0)($1)
	lui	$1, %hi($CPI2_2)
	ldc1	$f6, %lo($CPI2_2)($1)
	lui	$1, %hi($CPI2_3)
	ldc1	$f8, %lo($CPI2_3)($1)
	lui	$1, %hi($CPI2_4)
	ldc1	$f10, %lo($CPI2_4)($1)
	lui	$1, %hi($CPI2_5)
	ldc1	$f12, %lo($CPI2_5)($1)
$BB2_1:
	cvt.d.s	$f14, $f0
	madd.d	$f16, $f8, $f14, $f6
	add.d	$f18, $f14, $f4
	add.d	$f20, $f14, $f2
	mul.s	$f1, $f0, $f0
	add.d	$f14, $f14, $f10
	addiu	$2, $2, -1
	cvt.d.s	$f22, $f1
	mul.d	$f18, $f20, $f18
	mul.d	$f14, $f14, $f18
	add.d	$f16, $f22, $f16
	mul.d	$f16, $f16, $f12
	cvt.s.d	$f1, $f16
	cvt.s.d	$f14, $f14
	div.s	$f1, $f14, $f1
	bnez	$2, $BB2_1
	add.s	$f0, $f0, $f1
	trunc.w.s	$f0, $f0
	mfc1	$2, $f0
	ldc1	$f20, 0($sp)
	ldc1	$f22, 8($sp)
	jr	$ra
	addiu	$sp, $sp, 16
	.set	at
	.set	macro
	.set	reorder
	.end	main
$func_end2:
	.size	main, ($func_end2)-main


	.ident	"ecc 0.1.17 based on clang version 3.8.0 (trunk) (based on LLVM 3.8.0svn)"
	.section	".note.GNU-stack","",@progbits
	.text
