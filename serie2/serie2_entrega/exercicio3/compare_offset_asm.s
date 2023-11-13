/*
int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue) {
	return k < values[i][j].len && values[i][j].offset[k] == avalue->offset[k];
}
*/

	.text
	.global	compare_offset
compare_offset:

	ret

	.section .note.GNU-stack
