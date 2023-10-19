#include <stdio.h>
#include <limits.h>
#include <math.h>

#define NaN -1

unsigned long max_value(unsigned nchars){
    /**
     * Calculates the largest unsigned long that can be stored in a given number of bytes.
     * Returns 0 if the calculated number cannot be represented as an unsigned long.
     * 
     * Args:
     *      unsigned nchars: Number of bytes.
     * 
     * Return:
     *      unsigned long: Largest unsigned long that can be represented in [nchars] bytes.
     * 
     */
    unsigned long bits = CHAR_BIT * nchars;
    unsigned long umax_value = (unsigned long) (pow(2, bits - 1)) - 1;
    if(umax_value == NaN)
        return 0;
    return umax_value;
}

/*
int main(){
    unsigned arg = 0;
    printf("[%d bits] The biggest possible value is +%ld \n", arg, max_value(arg));
    return 0;
}
*/