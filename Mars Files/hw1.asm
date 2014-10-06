# Homework #1
#name: Aditya Balwani
#sbuid: 109353920
#---------------------------------------------------------------------------------------------------------------
#Output for AbCd, stored in Little Endian format as 100679865 : 
#----------------------------------------------------------------------------------------------------------------
#2's compliment:		100679865	0x060040b9	00000110000000000100000010111001	100679865
#1's Compliment:		100679865	0x060040b9	00000110000000000100000010111001	100679865
#Sign Magnitude:		100679865	0x060040b9	00000110000000000100000010111001	100679865
#Neg 2's Compliment:		-100679865	0xf9ffbf47	11111001111111111011111101000111	-100679865
#16-bit 2's comp:		16569		0x000040b9	00000000000000000100000010111001	16569

.text
	.globl main
	main: 
		#---------------------------------------------------------------------------
		#-------------------------------Data Entry----------------------------------
		#---------------------------------------------------------------------------
		la $a0, enterInt
		li $v0, 4
		syscall
		
		li $v0, 5
		syscall
		move $t0,$v0
		
		la $a0, newline
		li $v0, 4
		syscall
		
		
		#---------------------------------------------------------------------------
		#-------------------------------2's Compliment------------------------------
		#---------------------------------------------------------------------------
		
		la $a0, comp2
		li $v0, 4
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t0)
		li $v0, 1
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t0)
		li $v0, 34
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t0)
		li $v0, 35
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t0)
		li $v0, 1
		syscall
		
		
		#---------------------------------------------------------------------------
		#-------------------------------1's Compliment------------------------------
		#---------------------------------------------------------------------------
		
		la $a0, newline
		li $v0, 4
		syscall
		
		la $a0, comp1
		li $v0, 4
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		bgtz $t0, else
		li $t2, 1
		sub $t1, $t0, $t2
		j end
		
		else: la $t1, ($t0)
		end:
		la $a0, ($t1)
		li $v0, 100
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 34
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 35
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 1
		syscall
		
		
		#---------------------------------------------------------------------------
		#-------------------------------Sign Magnitude------------------------------
		#---------------------------------------------------------------------------
		
		la $a0, newline
		li $v0, 4
		syscall
		
		la $a0, signMag
		li $v0, 4
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		bgtz $t0, else2
		xori $t1, $t1, 0x7FFFFFFF
		j end2
		else2: 
		la $t1, ($t0)
		end2:
			
		la $a0, ($t1)
		li $v0, 101
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 34
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 35
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 1
		syscall
		
		#---------------------------------------------------------------------------
		#-------------------------------Neg 2's compliment--------------------------
		#---------------------------------------------------------------------------
		
		la $a0, newline
		li $v0, 4
		syscall
		
		la $a0, comp2neg
		li $v0, 4
		syscall
		
		li $t2, -1
		mul $t1, $t0, $t2
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 1
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 34
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 35
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 1
		syscall
		#---------------------------------------------------------------------------
		#-------------------------------16-bit 2's Compliment-----------------------
		#---------------------------------------------------------------------------
		
		la $a0, newline
		li $v0, 4
		syscall
		
		la $a0, comp2bit16
		li $v0, 4
		syscall
		
		andi $t1, $t0, 0xFFFF
		
		la $a0, ($t1)
		li $v0, 102
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 34
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 35
		syscall
		
		la $a0, tab
		li $v0, 4
		syscall
		
		la $a0, ($t1)
		li $v0, 1
		syscall
		
		li $v0, 10
		syscall
		
		
.data 
	enterInt: .asciiz "Enter and Integer : " 
	comp2: .asciiz "2's compliment:\t"
	comp1: .asciiz "1's Compliment:\t"
	signMag: .asciiz "Sign Magnitude:\t"
	comp2neg: .asciiz "Neg 2's Compliment:"
	comp2bit16: .asciiz "16-bit 2's comp:\t"
	newline: .asciiz "\n"
	tab: .asciiz "\t"
	one: .word 1
