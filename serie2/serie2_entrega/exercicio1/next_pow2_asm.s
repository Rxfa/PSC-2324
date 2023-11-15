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
	mov $0, %rax
	mov $1, %rsi # mask = 1
	bsr %rdi, %rcx 
	shl %cl, %rsi # mask <<= ((sizeof mask * CHAR_BIT) - 1)
	cmp $0, %rdi
	je .L0_next_pow2 # return 0
	cmp %rdi, %rsi
	ja .L0_next_pow2 # return 0
	mov %rsi, %rax
	jmp .L1_next_pow2
.L2_next_pow2:
	shr $1, %rax # mask >>= 1
.L1_next_pow2:
	test %rax, %rdi # (x & mask) == 0
	jz .L2_next_pow2
	cmp %rax, %rdi # x != mask
	jz .L0_next_pow2
	shl $1, %rax # mask << 1
.L0_next_pow2:
	ret
	.section .note.GNU-stack
