#include <stdio.h>
#include <limits.h>
#include <math.h>

#define ULONG_BIT CHAR_BIT * sizeof(unsigned long)

unsigned long max_value(unsigned nchars){
    unsigned long numOfBits = CHAR_BIT * nchars;
    //  printf("%ld \n", numOfBits);
    if(numOfBits < ULONG_BIT){
        unsigned long max_value = (unsigned long) pow(2, numOfBits);
        max_value = (max_value >> 1) - 1;
        return max_value;
    } else {
        return 0;
    }
}

int main(){
    printf("The biggest possible value is +%ld \n", max_value(1));
    return 0;
}