##
## dec.asm ask user for decimal number.
## convert to ASCII string, print the result
##
##	t0 - number read in, each quotient in turn
##	t1 - points to memory for string
##	t2 - each byte for the string in turn
##

#################################################################
#								#
#			text segment				#
#								#
#################################################################

	.text
	.globl main
main:
	la $a0,prompt	# print prompt on terminal
	li $v0,4
	syscall

	li $v0,5	# syscall 5 reads an integer
	syscall	
	move $t0,$v0	# $t0 holds number

	la $t1,result	# answer string set up here
	addi $t1,$t1,11

	li $t2,0
	sb $t2,($t1)	# save in string
	addi $t1,$t1,-1	# adjust destination pointer
	li $t2,'\n'
	sb $t2,($t1)	# save in string

	li $t9, 10
loop:	div  $t0, $t9	# get the remainder
	mfhi $t2	# move the qoutient from the HI register to $t2
	addi $t2,$t2,48	# convert to ASCII code
	addi $t1,$t1,-1	# adjust destination pointer
	sb $t2,($t1)	# save in string
	div $t0,$t9	# calculate quotient
	mflo $t0	# move 	qoutient from LO register
	bnez $t0,loop	# and continue if quotient>0

	la $a0,ans1	# print string before result
	li $v0,4
	syscall

	move $a0,$t1	# print result on terminal
	li $v0,4
	syscall

	move $a0,$t1	# print result on terminal
	li $v0,4
	syscall

	li $v0,10	# au revoir...
	syscall

#################################################################
#								#
#			data segment				#
#								#
#################################################################

	.data
result: .space 12
ans1:	.asciiz "ASCII string is "
prompt:	.asciiz "Enter decimal number: "

##
## end of file dec.asm
