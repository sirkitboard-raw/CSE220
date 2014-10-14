#Homework #4
#Name : Aditya Balwani
#SBUID : 109353920
.data
	invalid_base: .asciiz "Invalid Base"
	.align 2
	m1: .space 101
	.align 2
	m2: .space 101
	.align 2
	result: .space 101
	nullChar: .byte '\0'
	newLineChar: .asciiz "\n"
	tabChar: .asciiz "\t"
	
.text
	remainder:
		add $t0, $zero, $a0
		add $t1, $zero, $a1
		blt $t0, $t1, end_remainder
			sub $t0, $t0, $t1
			la $a0, ($t0)
			la $a1, ($t1)
			addi $sp, $sp, -4
			sw $ra, 0($sp)
			jal remainder
			lw $ra, 0($sp)
			addi $sp, $sp, 4
			jr $ra
		end_remainder:
		add $v0, $zero, $t0
		jr $ra
		
	printBase:
		add $t0, $zero, $a0
		add $t1, $zero, $a1
		li $t2, 2
		li $t3, 9
		blt $t1, $t2, invalidBase
		bgt $t1, $t3, invalidBase
			div $t0,$t1
			mflo $t2
			beqz $t2, printRem
				addi $sp, $sp, -8
				sw $ra, 0($sp)
				sw $t0, 4($sp)
				la $a0, ($t2)
				jal printBase
				lw $t0, 4($sp)
				lw $ra, 0($sp)
				addi $sp, $sp, 8
			printRem:
				la $a0, ($t0)
				la $a1, ($t1)
				addi $sp, $sp, -4
				sw $ra, 0($sp)
				jal remainder
				lw $ra, 0($sp)
				addi $sp, $sp, 4
				move $a0, $v0
				li $v0, 1
				syscall
				jr $ra
		invalidBase:
			la $a0, invalid_base
			li $v0, 4
			syscall
		jr $ra
	
	levenshteinDistance:
		add $t0, $zero, $a1
		add $t1, $zero, $a3		
		add $t2, $zero, $a0
		add $t3, $zero, $a2
		beqz $t0, returnLenT
		beqz $t1, returnLenS
			addi $t4, $t0, -1
			addi $t5, $t1, -1
			add $t6, $t2, $t4
			add $t7, $t3, $t5
			lb $t6, ($t6)
			lb $t7, ($t7)
			bne $t6, $t7, levenshElse
				li $t7, 0
				j returnLevensh
				levenshElse:
					li $t7, 1
			returnLevensh:
			addi $t2, $t0, -1
			addi $t3, $t1, -1
			addi $sp, $sp, -16
			sw $ra, 0($sp)
			sw $t0, 4($sp)
			sw $t1, 8($sp)
			sw $t7, 12($sp)
			la $a1, ($t2)
			la $a3, ($t1)
			jal levenshteinDistance
			lw $t7, 12($sp)
			lw $t1, 8($sp)
			lw $t0, 4($sp)
			lw $ra, 0($sp)
			addi $sp, $sp, 16
			add $t4, $zero, $v0
			
			addi $t2, $t0, -1
			addi $t3, $t1, -1
			addi $sp, $sp, -20
			sw $ra, 0($sp)
			sw $t0, 4($sp)
			sw $t1, 8($sp)
			sw $t7, 12($sp)
			sw $t4, 16($sp)
			la $a1, ($t0)
			la $a3, ($t3)
			jal levenshteinDistance
			lw $t4, 16($sp)
			lw $t7, 12($sp)
			lw $t1, 8($sp)
			lw $t0, 4($sp)
			lw $ra, 0($sp)
			addi $sp, $sp, 20
			add $t5, $zero, $v0
			
			addi $t2, $t0, -1
			addi $t3, $t1, -1
			addi $sp, $sp, -24
			sw $ra, 0($sp)
			sw $t0, 4($sp)
			sw $t1, 8($sp)
			sw $t7, 12($sp)
			sw $t4, 16($sp)
			sw $t5, 20($sp)
			la $a1, ($t2)
			la $a3, ($t3)
			jal levenshteinDistance
			lw $t5, 20($sp)
			lw $t4, 16($sp)
			lw $t7, 12($sp)
			lw $t1, 8($sp)
			lw $t0, 4($sp)
			lw $ra, 0($sp)
			addi $sp, $sp, 24
			add $t6, $zero, $v0
			
			addi $t4, $t4, 1
			addi $t5, $t5, 1
			add $t6, $t6, $t7
			
			add $t2, $zero, $a0
			add $t3, $zero, $a2
			addi $sp, $sp, -12
			sw $ra, 0($sp)
			sw $t2, 4($sp)
			sw $t3, 8($sp)
			la $a0, ($t4)
			la $a1, ($t5)
			la $a2, ($t6)
			jal minimum
			lw $ra, 0($sp)
			lw $t2, 4($sp)
			lw $t3, 8($sp)
			addi $sp, $sp, 12
			la $a0, ($t2)
			la $a2, ($t3)
			jr $ra
		returnLenS:
			add $v0, $zero, $t0
			jr $ra
		returnLenT:
			add $v0, $zero, $t1
			jr $ra
	
	strlen:
		li $t0, 0
		add $t1, $zero, $a0
		lengthLoop:
			lb $t3,($t1)
			beqz $t3, returnLength
			addi $t0, $t0, 1
			addi $t1, $t1, 1
			j lengthLoop
		returnLength:
			add $v0, $t0, $zero
		jr $ra
	
	minimum:
		add $t0, $zero, $a0
		add $t1, $zero, $a1
		add $t2, $zero, $a2
		checkA:
			bgt $t0, $t1, checkBA
			bgt $t0, $t2, returnC
			add $v0, $t0, $zero
			jr $ra
		checkBA:
			bgt $t1, $t2, returnC
			add $v0, $t1, $zero
			jr $ra
		returnC: 
			add $v0, $t2, $zero
			jr $ra
		
	rd100Chars:
		add $t0, $zero, $a0
		add $t5, $zero, $a0
		add $t6, $zero, $a1
		add $t7, $zero, $a2
		la $a0, ($t6)
		li $v0, 4
		syscall
		
		la $a0, ($t0)
		li $a1, 101
		li $v0, 8
		syscall
		
		li $t1, 0
		li $t2, 100
		la $t0, ($t5)
		add $t0, $zero, $a0
		lengthLoop2:
			lb $t3,($t0)
			beqz $t3, readAgain
			addi $t0, $t0, 1
			addi $t1, $t1, 1
			beq $t1, $t2, finishRead
			j lengthLoop2
		readAgain:
			la $a0, ($t7)
			li $v0, 4
			syscall
			
			la $a0, ($t5)
			la $a1, ($t6)
			la $a2, ($t7)
			j rd100Chars
		
		finishRead:
			addi $t0, $t0, 1
			lb $t1, nullChar
			sb $t1, 0($t0)
		jr $ra
		
	printIntMatrix:
		add $t0, $zero, $a0
		li $t1, 0
		printIntLoop:
			lw $t2, ($t0)
			la $a0, ($t2)
			li $v0, 1
			syscall
			la $a0, tabChar
			li $v0, 4
			syscall
			addi $t0, $t0, 4
			addi $t1, $t1, 4
			li $t3, 100
			li $t4, 5
			div $t1, $t4
			mfhi $t2
			bge $t1, $t3, endPrintIntMatrixLoop
			beqz $t2, printNewLine
			j printIntLoop
			printNewLine:
				la $a0, newLineChar
				li $v0, 4
				syscall	
			j printIntLoop
		endPrintIntMatrixLoop:
			la $a0, newLineChar
			li $v0, 4
			syscall
		jr $ra
	
	matrixMult:
		jr $ra
		
	
		
			
		
		