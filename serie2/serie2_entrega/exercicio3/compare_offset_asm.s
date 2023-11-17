/*
int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue) {
	return k < values[i][j].len && values[i][j].offset[k] == avalue->offset[k];
}
*/
	.text

	.equ value_size, 16
	.equ offset_ofs, 8
	.global	compare_offset
compare_offset:
	mov $0, %eax
	mov (%rdi, %rsi, 8), %rdi	# values[i]
	jmp .L0_compare_offset
.L1_compare_offset:
	add $value_size, %rdi # values[i] += value_size
	dec %edx # j--
.L0_compare_offset:
	cmp $0, %edx	# j == 0
	jnz .L1_compare_offset
	mov (%rdi), %r9	# values[i][j]
	cmp %ecx, %r9d		# values[i][j] - k > 0
	jbe .L2_compare_offset
	mov offset_ofs(%rdi), %rdi
	mov offset_ofs(%r8), %r8
	mov (%rdi, %rcx, 2), %di		# values[i][j].offset[k]
	mov (%r8, %rcx, 2), %r8w		# avalue->offset[k]
	cmp %r8w, %di				# avalue->offset[k] == values[i][j].offset[k]
	jnz .L2_compare_offset
	mov $1, %eax
.L2_compare_offset:
	ret

	.section .note.GNU-stack
