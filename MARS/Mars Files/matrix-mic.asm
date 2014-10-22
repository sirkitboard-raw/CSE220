.macro printtab
la $a0, tab
li $v0, 4
syscall
.end_macro

.macro printnewline
la $a0, newline
li $v0, 4
syscall
.end_macro

.data
str_prompt_m1: .asciiz "\nEnter a 100 character string for matrix 1: "
str_prompt_m2: .asciiz "\nEnter a 100 character string for matrix 2: "
str_error:  .asciiz "ERROR string is not 100 characters!\n"
str_m1:  .asciiz "\nMatrix 1:\n"
str_m2:  .asciiz "\nMatrix 2:\n"
.align 2
m1: .space 101
.align 2
m2: .space 101
.align 2

tab: .asciiz "\t"
newline: .asciiz "\n"

.text
.globl main
main:
 	la $a0, m1
    la $a1, str_prompt_m1
    la $a2, str_error
    jal rd100Chars

    # set arguments
    la $a0, m2
    la $a1, str_prompt_m2
    la $a2, str_error
    jal rd100Chars
    
    la $a0, str_m1
    li $v0, 4
    syscall

    la $a0, m1
    jal printIntMatrix

    # print label
    la $a0, str_m2
    li $v0, 4
    syscall

    la $a0, m2
    jal printIntMatrix
    
    li $v0, 10
    syscall

rd100Chars:
	addi $sp, $sp, -8		# Make room in stack
	sw $ra, 0($sp)			# Save the ra
	sw $a0, 4($sp)			# Store the argument 
	li $s0, 0			# Reset s0
	move $a0, $a1			# Print prompt
	li $v0, 4
	syscall
		
	lw $a0, 4($sp)			# Get back argument
	lw $ra, 0($sp)			# Return the ra
	addi $sp, $sp, 8		# Get back the room
	
	li $v0, 8			# Read string
	syscall				# Read string
	move $a3, $a0			# Put input into a0

readingChars:	
	lb $t0, ($a3)			# Read a character
	li $t1, 0x0000000A		# Load 
	beq $t0, $t1, readnull		# If read null, fly away
	addi $s0, $s0, 1		# Increment for each character
	addi $a3, $a3, 1		# Increment string
	j readingChars			# Keep reading
	
readnull:
	li $t2, 100			# Load 100 
	bne $s0, $t2, matrixerror	# If not 100, Error!
	
	jr $ra
	
matrixerror:
	move $t7, $a2			# Move error message to $a0
	move $a0, $t7			# Move it again
	li $v0, 4			# Calling 
	syscall				# Print ERROR!
	j rd100Chars			# Reprompt
	
printIntMatrix:
	addi $sp, $sp, -8		# Make room in stack
	sb $ra, 0($sp)			# Save the ra
	sb $a0, 4($sp)			# Store the argument
	move $a3, $a0	
	li $s0, 0			# Put input into a0
	
readPrint: 
	lw $t0, ($a3)			# Load characters
	addi $a3, $a3, 4		# Increment string
	addi $s0, $s0, 1
	move $a0, $t0			# Move read word to a0
	li $v0, 1			# Print word
	syscall
	printtab			# Increment counter
	li $t5, 5
	div $s0, $t5			# Check if counter is divisible by 5
	mfhi $t6			# Put remainder in t6
	beqz $t6, gonext		# If remainder is 0, go to next line
	
				# Print tab
	j readPrint			# Keep reading
	
gonext:
	li $t7, 25			# Load 25
	beq $t7, $s0, matrixdone	# If counter is 25 done
	printnewline			# Print new line if not 25
	j readPrint			# Go back
	
matrixdone:
	lw $a0, 4($sp)			# Get back argument
	lw $ra, 0($sp)			# Return the ra
	addi $sp, $sp, 8		# Get back the room
	jr $ra				# Return the funk
		
#matrixMult:
