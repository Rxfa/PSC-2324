#include <stdio.h>
#include <limits.h>

#define ULONG_BIT (CHAR_BIT * sizeof(unsigned long))
#define FULL 0xffffffffffffffff

unsigned long getmask(unsigned idx, unsigned len){
    /**
     * Calculates a mask out of a given length and starting index.
     * 
     * Args:
     *      unsigned idx: Starting Index.
     *      unsigned len: Length.
     * 
     * Return:
     *      unsigned long: Calculated mask.
     * 
     */
    unsigned long mask = FULL;
    unsigned rshifts = len;
    unsigned lshifts = idx % ULONG_BIT;
    if(len > ULONG_BIT)
        rshifts = len % ULONG_BIT;
    rshifts = ULONG_BIT - rshifts;
    mask >>= rshifts;
    mask <<= lshifts;
    return mask;
}

unsigned long getbits(unsigned long * data, unsigned index, unsigned length){
    /**
     * Given a bit vector, gets the bits over a given range.
     * 
     * Args:
     *      unsigned long * data: Bit vector.
     *      unsigned index: Starting index to get bits from.
     *      unsigned length: Number of bits to get, starting from the index.
     * 
     * Return:
     *      unsigned long: Bits between the [index]nth position of [data] and the [index + length - 1]nth position of [data].
     * 
     */
    unsigned current_vector = index / ULONG_BIT;
    unsigned max_vector = (index+length) / ULONG_BIT;
    unsigned used_bits = ULONG_BIT - index;
    unsigned long res = (data[current_vector] & getmask(index, length)) >> index;
    if((current_vector < max_vector) && ((length - used_bits) != 0)){
        res |= (data[max_vector] & getmask(0, length - used_bits)) << used_bits;
    }
    return res;
}

void setbits(unsigned long data[], unsigned index, unsigned length, unsigned long val){
    /**
     * Given a bit vector, sets to 1 the bits over a given range.
     * 
     * Args:
     *      unsigned long * data: Bit vector.
     *      unsigned index: Starting index to set to 1 the bits from.
     *      unsigned length: Number of bits to set to 1, starting from the index.
     * 
     * Return:
     *      void: Sets to 1 the bits between the [index]nth position of [data] and the [index + length - 1]nth position of [data].
     * 
     */
    unsigned current_vector = index / ULONG_BIT;
    unsigned max_vector = (index + length) / ULONG_BIT;
    unsigned used_bits = ULONG_BIT - index;
    data[current_vector] |= getmask(index, length);
    if((current_vector < max_vector) && ((length - used_bits) != 0))
        data[max_vector] |= getmask(0, length - used_bits);
}



/*
int main(){
    unsigned long data[] = {0xBFFFFFECABCD1234, 0xC, 2, 3};
    printf("[Result][0] - 0x%lx \n", getbits(data, 60, 8));
    return 0;
}
*/


