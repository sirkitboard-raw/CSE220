## start of file math1.asm
## 
## Question:
## calculate A*X^2+B*X+C
##
## Output format must be:
## "answer = 180"


#################################################################
#								#
#			text segment				#
#								#
#################################################################

	.text
	.globl main
main:
	lw $t0,X
	lw $t1,A
	lw $t2,B
	lw $t3,C
	
	mul $t4,$t0,$t0 # t4 = X^2
	mul $t4,$t4,$t1 # t4 = A*X^2
	mul $t5,$t2,$t0 # t5 = B*X
	add $t4,$t4,$t5 # t4 = A*X^2+B*X
	add $t4,$t4,$t3 # t4 = A*X^2+B*X+C

	la $a0,ans	# system call to print
	li $v0,4	# out string
	syscall	

	move $a0,$t4	# print result on terminal
	li $v0,1
	syscall

	la $a0,end1	# system call to print
	li $v0,4	# out a newline
	syscall

	li $v0,10
	syscall		# au revoir

#################################################################
#								#
#			data segment				#
#								#
#################################################################

	.data
X:	.word 7
A:	.word 3
B:	.word 4
C:	.word 5
ans:	.asciiz "answer = "
end1:	.asciiz "\n"
##
## End of file math1.asm