/*
	size_t next_pow2(size_t x){
		size_t mask = 1UL << ((sizeof mask * CHAR_BIT) - 1);
		if (x == 0 || x > mask)
			return 0;
		while ((x & mask) == 0)
			mask >>= 1;
		return mask << (x != mask);
	}
*/

	.global next_pow2
	.text
next_pow2:
	bsr %rdi, %rcx
	mov $1, %rax
	shl %cl, %rax
	cmp $0, %rdi
	jz .L0_next_pow2
	cmp %rax, %rdi
	jna .L1_next_pow2
.L1_next_pow2:
	jmp .L3_next_pow2
.L4_next_pow2:
	shr $1, %rax
.L3_next_pow2:
	test %rax, %rdi
	jz .L4_next_pow2
.L2_next_pow2:
	cmp %rax, %rdi
	jz .L5_next_pow2
	shl $1, %rax
	jmp .L5_next_pow2
.L0_next_pow2:
	mov $0, %rax
.L5_next_pow2:
	ret
	.section .note.GNU-stack
