#include <stdio.h>
#include <limits.h>

const unsigned long ULONG_BIT = CHAR_BIT * sizeof(unsigned long);

unsigned long getmask(unsigned idx, unsigned len){
    unsigned long mask = (0xffffffff >> (ULONG_BIT - len));
    mask <<= idx;
    return mask;
}

unsigned long getbits(unsigned long data[], unsigned index, unsigned length){
    unsigned long mask = getmask(index, length);
    unsigned long element = index / ULONG_BIT;
    return ((data[element] & mask) >> index);
}

void setbits(unsigned long data[], unsigned index, unsigned length, unsigned long val){
    unsigned mask = getmask(index, length);
    unsigned long element = index / ULONG_BIT;
    data[element] |= mask;
}

int main(){
    unsigned long data[] = {0xBFFFFFECABCD1234, 0xC, 2, 3};
    printf("0x%lx \n", getbits(data, 29, 8));
    return 0;
}