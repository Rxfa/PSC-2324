#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern size_t next_pow2(size_t arg);

int main(){
    size_t ans = next_pow2(17); 
    printf("%ld\n", ans);
    return 1;
}