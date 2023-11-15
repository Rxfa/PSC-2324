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
	cmovneq %rbx, token(%rip) # p = str
    pop %r12
	pop %rbp
	pop %rbx
	retq

	.section .note.GNU-stack
