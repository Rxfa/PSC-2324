/*
static void memswap(void *one, void *other, size_t width){
	char tmp[width];
	memcpy(tmp, one, width);
	memcpy(one, other, width);
	memcpy(other, tmp, width);
}
*/
	.text
memswap:
	push %rbx # one
	push %rbp # other
	push %r12 # width
	mov %rdx, %r12
	sub %r12, %rsp # tmp[width]
	mov %rdi, %rbx
	mov %rsi, %rbp
	mov %rsp, %rdi
	mov %rbx, %rsi
	call memcpy # memcpy(tmp, one, width) 
	mov %rbx, %rdi
	mov %rbp, %rsi
	call memcpy # memcpy(one, other, width)
	mov %rbp, %rdi
	mov %rsp, %rsi
	call memcpy # memcpy(other, tmp, width)
	add %r12, %rsp
	pop %r12
	pop %rbp
	pop %rbx
	ret

/*
void bubble_sort(
	void *base, 
	size_t nelements, 
	size_t width, 
	int (*compare)(const void *, const void *)
) {
	int swap_flg = 0;
	if (nelements <= 1)
		return;
	char *limit = (char *)base + (nelements - 1) * width;
	for (char *ptr = base; ptr < limit; ptr += width)
		if (compare(ptr, ptr + width) > 0) {
			memswap(ptr, ptr + width, width);
			swap_flg = 1;
		}
	if (swap_flg == 0)
		return;
	bubble_sort(base, nelements - 1, width, compare);
}
*/
	.text
	.global	bubble_sort
bubble_sort:
	push %rbx # base
	push %rbp # nelements
	push %r12 # width
	push %r13 # swap_flg
	push %r14 # limit
	push %r15 # ptr
	sub $8, %rsp # (*compare)(const void *, const void *)

	mov %rdi, %rbx
	mov %rsi, %rbp
	mov %rdx, %r12
	mov %rcx, (%rsp)
	mov  $0, %r13d # swap_flg = 0
	cmp	$1, %ebp # nelements - 1 <= 0
	jbe .L0_bubble_sort # return
	lea -1(%rbp), %rax # (nelements - 1)
	mul %r12d # (nelements - 1) * width
	lea (%rax, %rbx), %r14 # base + (nelements - 1) * width
	mov %rbx, %r15 # ptr = base
	jmp .L1_bubble_sort
.L2_bubble_sort:
	mov %r15, %rdi
	lea (%r15, %r12), %rsi
	call *(%rsp) # compare(ptr, ptr + width)
	cmp $0, %eax # compare(ptr, ptr + width) > 0
	jle .L3_bubble_sort
	mov %r15, %rdi
	lea (%r15, %r12), %rsi
	mov %r12, %rdx
	call memswap # memswap(ptr, ptr + width, width)
	mov $1, %r13d # swap_flg = 1
.L3_bubble_sort:
	add %r12, %r15 # ptr += width
.L1_bubble_sort: 
	cmp %r15, %r14 # 0 < limit - ptr
	ja .L2_bubble_sort
	cmp $0, %r13d # swap_flg == 0
	je .L0_bubble_sort # return
	mov %rbx, %rdi
	lea -1(%rbp), %rsi
	mov %r12, %rdx
	mov (%rsp), %rcx
	call bubble_sort # bubble_sort(base, nelements - 1, width, compare)
.L0_bubble_sort:
	add $8, %rsp
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbp
	pop %rbx
	ret
	.section .note.GNU-stack
