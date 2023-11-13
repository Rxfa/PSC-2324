    .globl next_pow2
    .text

next_pow2:
    mov $1, %eax
    bsr %edi, %ecx
    shl %cl, %eax # TODO -> check it cl is the right reg here
    cmp %eax, %edi
    jbe .L0_next_pow2
    shl $1, %eax
.L0_next_pow2:
    ret

    .section .note.GNU-stack

    .end
