.data

.text
.globl main
main:
li $t1, 3
li $t2, 3
li $t3, 3

la $a0, ($t1)
la $a1, ($t2)
la $a2, ($t3)
jal minimum

move $a0, $v0
li $v0, 1
syscall

li $v0, 10
syscall
.include "hw4.asm"

