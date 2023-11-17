/*
char *my_strtok(char *str, const char *sep){
	static char *p = NULL;
	if (str != NULL)
		p = str;
	if (p == NULL || *p == 0)
		return NULL;
	while (strchr(sep, *p) != NULL)
		++p;
	if (*p == 0)
		return NULL;
	char *q = p;
	while (*p != 0 && strchr(sep, *p) == NULL)
		++p;
	*p++ = 0;
	return q;
}
*/
	.bss
	token:
		.space 8
	.text
	.global my_strtok
my_strtok:
	push %rbx # str
	push %rbp # sep
	push %r12 # q
	mov %rdi, %rbx
	mov %rsi, %rbp
	cmp $0, %rbx # str != NULL
	je .L0_my_strtok
	mov %rbx, token(%rip) # p = str
.L0_my_strtok:
	cmpq $0, token(%rip) # p == NULL
	je .L7_my_strtok # return NULL
	mov token(%rip), %rsi
	cmpq $0, (%rsi) # *p == 0
	je .L7_my_strtok # return NULL
	jmp .L2_my_strtok
.L3_my_strtok:
	incq token(%rip) # ++p
.L2_my_strtok:
	mov token(%rip), %rsi
	mov (%rsi), %rsi
	mov %rbp, %rdi
	callq strchr
	cmpq $0, %rax # strchr(sep, *p) != NULL
	jne .L3_my_strtok
	mov $0, %rdx
	mov token(%rip), %rsi
	cmpq $0, (%rsi) # *p == 0
	je .L7_my_strtok # return NULL
	mov token(%rip), %r12 # char * q = p
	jmp .L4_my_strtok
.L5_my_strtok:
	incq token(%rip) # ++p
.L4_my_strtok:
	mov token(%rip), %rsi
	mov (%rsi), %rsi
	cmpq $0, %rsi # *p != 0
	je .L6_my_strtok
	mov %rbp, %rdi
	callq strchr
	cmp $0, %rax # strchr(sep, *p) == NULL
	je .L5_my_strtok
.L6_my_strtok:
	movq token(%rip), %rax
	movb $0, (%rax) # *p = 0
	incq token(%rip) # *p++
	mov %r12, %rax # return q
	jmp .L1_my_strtok
.L7_my_strtok:
	mov $0, %rax
.L1_my_strtok:
	pop %r12
	pop %rbp
	pop %rbx
	ret

	.section .note.GNU-stack
