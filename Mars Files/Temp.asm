##
## temp.asm ask user for temperature in Celcius,
##  convert to Fahrenheit, print the result.
##
##	v0 -  reads in celcius
##	t0 - holds Fahrenheit result
##	a0 - points to output strings
##

#########################################################
#							#
#			text segment			#
#							#
#########################################################

	.text
	.globl main
main:
	la $a0,prompt	#print prompt on terminal
	li $v0,4
	syscall
	
	li $v0,5	#syscall 5 reads an integer
	syscall
	
	li $t9, 9
	li $t8, 5
	mul $t0,$v0, $t9	#to convert, multiply by 9
	div $t0, $t8		#divide by 5, then
	addi $t0,$t0,32		#add 32

	la $a0,ans1	#print string before result
	li $v0,4
	syscall

	move $a0,$t0	#print result
	li $v0,1
	syscall

	la $a0,end1	#system call to print
	li $v0,4	#out a newline
	syscall

	li $v0,10
	syscall		#au revoir

#################################################################
#								#
#			data segment				#
#								#
#################################################################

	.data
	prompt:	.asciiz "Enter temperature (Celcius): "
	ans1:	.asciiz "The temperature in Fahrenheit is "
	end1:	.asciiz "\n"

	##
	## end of file temp.a
