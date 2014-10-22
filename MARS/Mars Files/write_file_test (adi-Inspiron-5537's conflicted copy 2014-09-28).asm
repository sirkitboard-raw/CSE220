.text
.globl main
main:
	la $a0, fileName
	li $a1, 1
	li $a2, 0
	li $v0, 13
	syscall
	move $t0, $v0
	
	la $a0, text1
	li $v0, 4
	syscall
	
	la $a0, handle_text
	la $a1, handle_text
	li $v0, 8
	syscall
	
	la $t2, utf8bom
	move $a0, $t0
	la $a1, ($t2)
	li $a2, 3
	li $v0, 15
	syscall
	
	move $a0, $t0
	la $a1, handle_text
	li $a2, 6
	li $v0, 15
	syscall
	

.data
	text1: .asciiz "Enter a word : "
	fileName: .asciiz "output.txt"
	handle_text: .space 20
	utf8bom: .word 0xBFBBEF
	
