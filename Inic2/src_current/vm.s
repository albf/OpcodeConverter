	.file	"vm.c"
	.text
	.globl	advance_pc
	.type	advance_pc, @function
advance_pc:
.LFB21:
	.cfi_startproc
	movl	nPC(%rip), %eax
	movl	%eax, PC(%rip)
	addl	%edi, %eax
	movl	%eax, nPC(%rip)
	ret
	.cfi_endproc
.LFE21:
	.size	advance_pc, .-advance_pc
	.globl	fetch
	.type	fetch, @function
fetch:
.LFB23:
	.cfi_startproc
	leal	3(%rdi), %eax
	movl	%edi, %edx
	movzbl	VM_memory(%rdx), %edx
	movzbl	VM_memory(%rax), %eax
	sall	$24, %edx
	orl	%edx, %eax
	leal	1(%rdi), %edx
	movzbl	VM_memory(%rdx), %edx
	sall	$16, %edx
	orl	%edx, %eax
	leal	2(%rdi), %edx
	movzbl	VM_memory(%rdx), %edx
	sall	$8, %edx
	orl	%edx, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	fetch, .-fetch
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%2x%2x%2x%2x\n"
	.text
	.globl	print_memory
	.type	print_memory, @function
print_memory:
.LFB24:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$VM_memory+3, %ebx
.L5:
	movzbl	-2(%rbx), %ecx
	movzbl	-3(%rbx), %edx
	xorl	%eax, %eax
	movzbl	(%rbx), %r9d
	movzbl	-1(%rbx), %r8d
	movl	$.LC0, %esi
	movl	$1, %edi
	addq	$4, %rbx
	call	__printf_chk
	cmpq	$VM_memory+1703, %rbx
	jne	.L5
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	print_memory, .-print_memory
	.section	.rodata.str1.1
.LC1:
	.string	"%d:%x\n"
	.text
	.globl	print_registers
	.type	print_registers, @function
print_registers:
.LFB25:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%ebx, %ebx
.L10:
	movl	RF(,%rbx,4), %ecx
	leal	1(%rbx), %edx
	xorl	%eax, %eax
	movl	$.LC1, %esi
	movl	$1, %edi
	incq	%rbx
	call	__printf_chk
	cmpq	$32, %rbx
	jne	.L10
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	print_registers, .-print_registers
	.globl	vm_cpu
	.type	vm_cpu, @function
vm_cpu:
.LFB22:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	orl	$-1, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	%esi, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	xorl	%ebp, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	pushq	%rcx
	.cfi_def_cfa_offset 64
	movl	%edi, PC(%rip)
	movl	$4, nPC(%rip)
	movl	$0, RF(%rip)
	movl	$1, RF+124(%rip)
.L13:
	movl	PC(%rip), %r15d
	movl	%r15d, %edi
	call	fetch
	movl	%eax, %r8d
	movl	%eax, %edx
	movl	%eax, %esi
	movl	%eax, %edi
	shrl	$21, %r8d
	shrl	$16, %edx
	shrl	$11, %esi
	movl	%eax, %ecx
	shrl	$26, %edi
	andl	$31, %r8d
	andl	$31, %edx
	andl	$31, %esi
	andl	$67108863, %ecx
	cmpl	$46, %edi
	ja	.L84
	jmp	*.L16(,%rdi,8)
	.section	.rodata
	.align 8
	.align 4
.L16:
	.quad	.L15
	.quad	.L17
	.quad	.L103
	.quad	.L19
	.quad	.L20
	.quad	.L21
	.quad	.L22
	.quad	.L23
	.quad	.L25
	.quad	.L25
	.quad	.L27
	.quad	.L27
	.quad	.L28
	.quad	.L29
	.quad	.L30
	.quad	.L31
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L32
	.quad	.L31
	.quad	.L33
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L34
	.quad	.L39
	.quad	.L36
	.quad	.L37
	.quad	.L38
	.quad	.L39
	.quad	.L40
	.quad	.L84
	.quad	.L41
	.quad	.L42
	.quad	.L43
	.quad	.L44
	.quad	.L84
	.quad	.L84
	.quad	.L45
	.text
.L15:
	movl	%eax, %ecx
	andl	$63, %eax
	shrl	$6, %ecx
	andl	$31, %ecx
	cmpb	$43, %al
	ja	.L84
	movzbl	%al, %eax
	jmp	*.L47(,%rax,8)
	.section	.rodata
	.align 8
	.align 4
.L47:
	.quad	.L46
	.quad	.L84
	.quad	.L48
	.quad	.L49
	.quad	.L50
	.quad	.L84
	.quad	.L51
	.quad	.L51
	.quad	.L53
	.quad	.L54
	.quad	.L55
	.quad	.L56
	.quad	.L57
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L58
	.quad	.L59
	.quad	.L60
	.quad	.L61
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L63
	.quad	.L63
	.quad	.L65
	.quad	.L65
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L84
	.quad	.L67
	.quad	.L67
	.quad	.L69
	.quad	.L69
	.quad	.L70
	.quad	.L71
	.quad	.L72
	.quad	.L73
	.quad	.L84
	.quad	.L84
	.quad	.L75
	.quad	.L75
	.text
.L56:
	andl	$31, %edx
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%rdx,4)
	je	.L14
	jmp	.L106
.L55:
	andl	$31, %edx
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%rdx,4)
	jne	.L14
.L106:
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%r8,4), %eax
	movl	%eax, RF(,%rsi,4)
	jmp	.L14
.L67:
	andl	$31, %edx
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%rdx,4), %eax
	addl	RF(,%r8,4), %eax
	jmp	.L107
.L70:
	andl	$31, %edx
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%rdx,4), %eax
	andl	RF(,%r8,4), %eax
.L107:
	movl	%eax, RF(,%rsi,4)
	jmp	.L84
.L65:
	andl	$31, %r8d
	movq	%rdx, %rdi
	xorl	%edx, %edx
	movl	RF(,%r8,4), %eax
	andl	$31, %edi
	divl	RF(,%rdi,4)
	movl	%edx, %ebp
	movl	%eax, %r12d
	jmp	.L84
.L63:
	andl	$31, %edx
	andl	$31, %r8d
	movl	RF(,%r8,4), %eax
	movl	RF(,%rdx,4), %r12d
	imulq	%rax, %r12
	movq	%r12, %rax
	shrq	$32, %rax
	movq	%rax, %rbp
	jmp	.L84
.L73:
	andl	$31, %edx
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%rdx,4), %eax
	orl	RF(,%r8,4), %eax
	notl	%eax
	jmp	.L107
.L71:
	andl	$31, %edx
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%rdx,4), %eax
	orl	RF(,%r8,4), %eax
	jmp	.L107
.L46:
	andl	$31, %esi
	andl	$31, %edx
	jmp	.L112
.L50:
	andl	$31, %r8d
	andl	$31, %esi
	andl	$31, %edx
	movl	RF(,%r8,4), %ecx
.L112:
	movl	RF(,%rdx,4), %eax
	sall	%cl, %eax
	jmp	.L107
.L49:
	andl	$31, %edx
	movzbl	%sil, %esi
	movl	RF(,%rdx,4), %edx
	testl	%edx, %edx
	jns	.L76
	testb	%cl, %cl
	je	.L76
	movl	%r14d, %eax
	shrl	%cl, %eax
	notl	%eax
	orl	%edx, %eax
	jmp	.L107
.L76:
	sarl	%cl, %edx
	movl	%edx, RF(,%rsi,4)
	jmp	.L84
.L48:
	andl	$31, %esi
	andl	$31, %edx
.L114:
	movl	RF(,%rdx,4), %eax
	shrl	%cl, %eax
	jmp	.L107
.L51:
	andl	$31, %r8d
	andl	$31, %esi
	andl	$31, %edx
	movl	RF(,%r8,4), %ecx
	jmp	.L114
.L69:
	andl	$31, %r8d
	andl	$31, %edx
	andl	$31, %esi
	movl	RF(,%r8,4), %eax
	subl	RF(,%rdx,4), %eax
	jmp	.L107
.L72:
	andl	$31, %edx
	andl	$31, %esi
	andl	$31, %r8d
	movl	RF(,%rdx,4), %eax
	jmp	.L113
.L75:
	andl	$31, %edx
	andl	$31, %r8d
	andl	$31, %esi
	movl	RF(,%rdx,4), %eax
	cmpl	%eax, RF(,%r8,4)
	setb	%al
	movzbl	%al, %eax
	jmp	.L107
.L54:
	addl	$8, %r15d
	movl	%r15d, RF+124(%rip)
.L53:
	movl	nPC(%rip), %eax
	andl	$31, %r8d
	movl	%eax, PC(%rip)
	movl	RF(,%r8,4), %eax
	movl	%eax, nPC(%rip)
	jmp	.L13
.L58:
	andl	$31, %esi
	movl	%ebp, RF(,%rsi,4)
	jmp	.L84
.L60:
	andl	$31, %esi
	movl	%r12d, RF(,%rsi,4)
	jmp	.L84
.L59:
	andl	$31, %r8d
	movl	RF(,%r8,4), %ebp
	jmp	.L84
.L61:
	andl	$31, %r8d
	movl	RF(,%r8,4), %r12d
	jmp	.L84
.L57:
	movzbl	RF+8(%rip), %edi
	call	syscall
	testb	%al, %al
	setne	%bl
	jmp	.L14
.L25:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	jmp	.L108
.L28:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	andl	RF(,%r8,4), %eax
	jmp	.L108
.L29:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	orl	RF(,%r8,4), %eax
	jmp	.L108
.L30:
	andl	$31, %esi
	andl	$31, %r8d
	cwtl
.L113:
	xorl	RF(,%r8,4), %eax
	jmp	.L107
.L31:
	andl	$31, %edx
	sall	$16, %eax
	jmp	.L108
.L32:
	andl	$31, %edx
	cwtl
	jmp	.L108
.L27:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	cmpl	%eax, RF(,%r8,4)
	setb	%al
	movzbl	%al, %eax
	jmp	.L108
.L17:
	andl	$31, %edx
	movl	RF(,%rdx,4), %edx
	cmpl	$1, %edx
	jne	.L78
	andl	$31, %r8d
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%r8,4)
	jns	.L104
	jmp	.L14
.L78:
	cmpl	$17, %edx
	jne	.L79
	andl	$31, %r8d
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%r8,4)
	jns	.L105
	jmp	.L14
.L79:
	testl	%edx, %edx
	jne	.L80
	andl	$31, %r8d
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%r8,4)
	jns	.L14
	jmp	.L104
.L80:
	xorl	%ebx, %ebx
	cmpl	$16, %edx
	jne	.L14
	andl	$31, %r8d
	cmpl	$0, RF(,%r8,4)
	jns	.L14
.L105:
	addl	$8, %r15d
	movl	%r15d, RF+124(%rip)
	jmp	.L104
.L20:
	andl	$31, %edx
	andl	$31, %r8d
	xorl	%ebx, %ebx
	movl	RF(,%rdx,4), %edi
	cmpl	%edi, RF(,%r8,4)
	jne	.L14
	jmp	.L104
.L23:
	andl	$31, %r8d
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%r8,4)
	jg	.L104
	jmp	.L14
.L22:
	andl	$31, %r8d
	xorl	%ebx, %ebx
	cmpl	$0, RF(,%r8,4)
	jg	.L14
	jmp	.L104
.L21:
	andl	$31, %edx
	andl	$31, %r8d
	xorl	%ebx, %ebx
	movl	RF(,%rdx,4), %edi
	cmpl	%edi, RF(,%r8,4)
	je	.L14
.L104:
	cwtl
	leal	0(,%rax,4), %edi
	call	advance_pc
	jmp	.L13
.L34:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	movb	VM_memory(%rax), %cl
	movb	%cl, %al
	andl	$127, %ecx
	andl	$-128, %eax
	movzbl	%al, %eax
	sall	$24, %eax
	orl	%ecx, %eax
	jmp	.L108
.L38:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	jmp	.L109
.L39:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	incl	%eax
.L109:
	movzbl	VM_memory(%rax), %eax
.L108:
	movl	%eax, RF(,%rdx,4)
	jmp	.L84
.L37:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	leal	3(%rax), %ecx
	movl	%eax, %esi
	movzbl	VM_memory(%rsi), %esi
	movzbl	VM_memory(%rcx), %ecx
	sall	$24, %esi
	orl	%esi, %ecx
	leal	1(%rax), %esi
	addl	$2, %eax
	movzbl	VM_memory(%rax), %eax
	movzbl	VM_memory(%rsi), %esi
	sall	$8, %eax
	sall	$16, %esi
	orl	%esi, %ecx
	jmp	.L110
.L41:
	andl	$31, %r8d
	andl	$31, %edx
	cwtl
	movl	RF(,%rdx,4), %edx
	addl	RF(,%r8,4), %eax
	jmp	.L111
.L42:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	movl	RF(,%rdx,4), %edx
	movzbl	%dh, %esi
	movl	%eax, %ecx
	incl	%eax
	movb	%sil, VM_memory(%rcx)
	jmp	.L111
.L44:
	andl	$31, %r8d
	andl	$31, %edx
	cwtl
	movl	RF(,%rdx,4), %edx
	addl	RF(,%r8,4), %eax
	movl	%edx, %esi
	movl	%eax, %ecx
	shrl	$24, %esi
	movb	%sil, VM_memory(%rcx)
	leal	1(%rax), %ecx
	movl	%edx, %esi
	shrl	$16, %esi
	movb	%sil, VM_memory(%rcx)
	leal	2(%rax), %ecx
	movzbl	%dh, %esi
	addl	$3, %eax
	movb	%sil, VM_memory(%rcx)
	jmp	.L111
.L19:
	addl	$8, %r15d
	movl	%r15d, RF+124(%rip)
.L103:
	movl	nPC(%rip), %eax
	sall	$2, %ecx
	movl	%ecx, nPC(%rip)
	movl	%eax, PC(%rip)
	jmp	.L13
.L33:
	movzbl	%al, %edi
	call	syscall
	jmp	.L84
.L43:
	andl	$31, %r8d
	andl	$31, %edx
	cwtl
	movl	RF(,%rdx,4), %edx
	addl	RF(,%r8,4), %eax
	movl	%edx, %esi
	shrl	$16, %edx
	movl	%eax, %ecx
	shrl	$24, %esi
	incl	%eax
	movb	%sil, VM_memory(%rcx)
.L111:
	movb	%dl, VM_memory(%rax)
	jmp	.L84
.L45:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	movl	RF(,%rdx,4), %edx
	movl	%eax, %ecx
	decl	%eax
	movb	%dl, VM_memory(%rcx)
	movb	$0, VM_memory(%rax)
	jmp	.L84
.L36:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	leal	1(%rax), %ecx
	movzbl	VM_memory(%rax), %eax
	movzbl	VM_memory(%rcx), %ecx
	sall	$24, %eax
	sall	$16, %ecx
	jmp	.L110
.L40:
	andl	$31, %r8d
	cwtl
	andl	$31, %edx
	addl	RF(,%r8,4), %eax
	leal	-1(%rax), %ecx
	movzbl	VM_memory(%rax), %eax
	movzbl	VM_memory(%rcx), %ecx
	sall	$8, %ecx
.L110:
	orl	%eax, %ecx
	movl	%ecx, RF(,%rdx,4)
.L84:
	xorl	%ebx, %ebx
.L14:
	movl	$4, %edi
	call	advance_pc
	testb	%bl, %bl
	je	.L13
	testl	%r13d, %r13d
	je	.L12
	call	print_memory
	popq	%rdx
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	print_registers
.L12:
	.cfi_restore_state
	popq	%rax
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	vm_cpu, .-vm_cpu
	.globl	nPC
	.data
	.align 4
	.type	nPC, @object
	.size	nPC, 4
nPC:
	.long	4
	.globl	PC
	.bss
	.align 4
	.type	PC, @object
	.size	PC, 4
PC:
	.zero	4
	.globl	VM_memory
	.align 16
	.type	VM_memory, @object
	.size	VM_memory, 1700
VM_memory:
	.zero	1700
	.comm	RF,128,16
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
