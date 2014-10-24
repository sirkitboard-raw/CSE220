# hw3_main2.asm
# Do NOT modify this file.
# This file is NOT part of your homework 3 submission.
.data
pi: .float 3.1415926535897924
input: .space 50
prompt_float: .asciiz "Enter a floating point value: "
prompt_radius: .asciiz "Enter a radius: "
arclength: .asciiz "Arc length s: "


# Constants
.eqv QUIT 10
.eqv PRINT_STRING 4
.eqv PRINT_FLOAT 2
.eqv READ_STRING 8

.text
.globl _start



####################################################################
# This is the "main" of your program; Everything starts here.
####################################################################

_start:
	li $t0, 0x00000000
	mtc1 $t0, $f0
	mtc1 $t0, $f1
	mtc1 $t0, $f2
	mtc1 $t0, $f3
	mtc1 $t0, $f4
	mtc1 $t0, $f5
	mtc1 $t0, $f6
	mtc1 $t0, $f7
	mtc1 $t0, $f8
	mtc1 $t0, $f9
	mtc1 $t0, $f10
	mtc1 $t0, $f11
	mtc1 $t0, $f12
	mtc1 $t0, $f13
	mtc1 $t0, $f14
	mtc1 $t0, $f15
	mtc1 $t0, $f16
	mtc1 $t0, $f17
	mtc1 $t0, $f18
	mtc1 $t0, $f19
	mtc1 $t0, $f20
	mtc1 $t0, $f21
	mtc1 $t0, $f22
	mtc1 $t0, $f23
	mtc1 $t0, $f24
	mtc1 $t0, $f25
	mtc1 $t0, $f26
	mtc1 $t0, $f27
	mtc1 $t0, $f28
	mtc1 $t0, $f29
	mtc1 $t0, $f30
	mtc1 $t0, $f31
	
	
	li $t0, -1
	li $t1, -1
	li $t2, -1
	li $t3, -1
	li $t4, -1
	li $t5, -1
	li $t6, -1
	li $t7, -1
	li $t8, -1
	li $t9, -1
	li $s0, -1
	li $s1, -1
	li $s2, -1
	li $s3, -1
	li $s4, -1
	li $s5, -1
	li $s6, -1
	li $s7, -1
	
	
	li $v0, 1
	# Ask the user for value
	jal prompt_user

	# Store the return value from prompt user
	mov.s $f20, $f0

	# print_parts to be defined in your hw2.asm
	mov.s $f12, $f0
	jal print_parts

	# print_binary_product to be defined in your hw2.asm
	mov.s $f12, $f20
	jal print_binary_product

	# print radius prompt
	li $v0, PRINT_STRING
	la $a0, prompt_radius
	syscall

	# Get the user input
	li $v0, READ_STRING
	la $a0, input
	addi $a1, $zero, 49
	syscall

	#arcLengthS to be defined in your hw2.asm
	mov.s $f12, $f20
	jal arcLengthS

	# Print the result of arcLength
	la $a0, arclength
	mov.s $f12, $f0
	jal print_msg_float

	# Exit the program
	li $v0, QUIT
	syscall

###################################################################
# End of MAIN program
####################################################################

####################################################################
# Function to print out a string and a float value
# void print_msg_float (string address, float value)
#
# Parameters passed:
# $a0 = address of msg to print
# $f12 = value to print
####################################################################

print_msg_float:

	# Allocate space on the stack to hold the value
	# Store the argument $a0 on the stack to preserve the value
	addi $sp, $sp, -4
	sw $a0, 0($sp)

	# Print message
	li $v0, PRINT_STRING

	# $a0 already has the string address
	syscall

	# Print float
	li $v0, PRINT_FLOAT

	# $f12 already has the float value
	syscall

	# Print newline
	li $v0, 11
	li $a0, '\n'
	syscall

	# Return the $a0 register to original value
	# Move the stack back to its initial position
	lw $a0, 0($sp)
	addi $sp, $sp, 4

	jr $ra

####################################################################
# Function which asks the user to enter a float value, calls atof
# function and then returns the float value
# float prompt_user (string address)
#
# Parameters passed:
# $a0 = address of msg to print
# $f0 = return value of user entered string value
####################################################################

prompt_user:

	# Push Address onto the stack
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	# Ask the user for a string
	li $v0, PRINT_STRING
	la $a0, prompt_float
	syscall

	li $v0, READ_STRING
	la $a0, input
	li $a1, 49 		# If you have a space of N this value should be (N-1), extra space holds the return character
	syscall

	# atof to be defined in your hw2.asm
	la $a0, input
	jal atof

	# return value from atof is expected to be in $f0
	# leave it there to return

	# Get $ra from the stack
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

#################################################################
# Student defined functions will be included starting here
#################################################################

.include "hw3.asm"
