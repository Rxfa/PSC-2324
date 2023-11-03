#include <stdio.h>

int indexOfMin(short * a, int b, int c){
    if(a[b] - a[c] > 0){
        return b;
    } else {
        return c;
    }
}

void swap(short * a, int i1, int i2){
    int temp = a[i1];
    a[i1] = a[i2];
    a[i2] = temp;
}

void sort(short * a, int size){
    int idxMin;
    for(int i = 0; i < size; i++){
        idxMin = i;
        for(int j = i+1; j < size; j++){
            idxMin = indexOfMin(a, idxMin, j);
        }
        swap(a, idxMin, i);
    }
}

void print_array(short * a, int size){
    for(int idx = 0; idx < 10; idx++){
        printf("%d \n", a[idx]);
    }
}

void selectionSort(short * a){
    int size = sizeof(a) / sizeof(a[0]); 
    sort(a, size);
    print_array(a, size);
}

void main(){
    short arr[] = {9, 6, 4, 2, 5, 1, 7, 3, 8, 0};
    selectionSort(arr);
}