#include <stdio.h>
void f0() {
	int data[] = {1, 2, 3, 4};
	int * pi = &data[3];
	
	char * pc = (char*)&data[1];
	
	int dif_chars = (char*)pi - pc;
	int dif_ints = pi - (int*)pc;
	
	printf("pi=%p, pc=%p\n", (void*)pi, (void*)pc);
	printf("*pi=%d, *pc=%d, dif_chars=%d, dif_ints=%d\n", 
			*pi, *pc, dif_chars, dif_ints);
			
	pc -= 3;
	dif_ints = pi - (int*)pc;
	printf("dif_ints=%d\n", dif_ints);
}

void swap(short *a, int l, int r) {
	short tmp = a[l];
	a[l] = a[r];
	a[r] = tmp;
}
void selection_sort(short * a, int size) {
	for (int i = 0; i < size-1; i++) {
		for (int j = 0; j < size-1; j++)
			if (a[j] > a[j+1])
				swap(a, j, j+1);
	}
}
void print_array(short * a, int size) {
	for (int i = 0; i < size-1; i++)
		printf("a[%d]=%d, ", i, *(a+i));
	if (size > 0)
		printf("a[%d]=%d\n", size-1, *(a+size-1));
}

int main() {
	short ex1[] = {1, -1, 4, 2, 7, 9};
	print_array(ex1, sizeof(ex1)/sizeof(ex1[0]));
	selection_sort(ex1, sizeof(ex1)/sizeof(ex1[0]));
	print_array(ex1, sizeof(ex1)/sizeof(ex1[0]));	
	
	return 0;
}
