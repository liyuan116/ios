	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	_objc_autoreleasePoolPush
	leaq	L__unnamed_cfstring_(%rip), %rsi
	movq	%rsi, %rdi
	movq	%rax, -32(%rbp)         ## 8-byte Spill
	callq	_objc_retain
	leaq	L__unnamed_cfstring_.2(%rip), %rsi
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rsi, %rdi
	movq	%rax, %rsi
	movb	$0, %al
	callq	_NSLog
	xorl	%ecx, %ecx
	movl	%ecx, %esi
	leaq	-24(%rbp), %rdi
	callq	_objc_storeStrong
	movq	-32(%rbp), %rdi         ## 8-byte Reload
	callq	_objc_autoreleasePoolPop
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"hello world"

	.section	__DATA,__cfstring
	.p2align	3               ## @_unnamed_cfstring_
L__unnamed_cfstring_:
	.quad	___CFConstantStringClassReference
	.long	1992                    ## 0x7c8
	.space	4
	.quad	L_.str
	.quad	11                      ## 0xb

	.section	__TEXT,__cstring,cstring_literals
L_.str.1:                               ## @.str.1
	.asciz	"%@"

	.section	__DATA,__cfstring
	.p2align	3               ## @_unnamed_cfstring_.2
L__unnamed_cfstring_.2:
	.quad	___CFConstantStringClassReference
	.long	1992                    ## 0x7c8
	.space	4
	.quad	L_.str.1
	.quad	2                       ## 0x2

	.section	__DATA,__objc_imageinfo,regular,no_dead_strip
L_OBJC_IMAGE_INFO:
	.long	0
	.long	64


.subsections_via_symbols
