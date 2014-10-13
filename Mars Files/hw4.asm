#Homework #4
#Name : Aditya Balwani
#SBUID : 109353920
.data
	invalid_base: .asciiz "Invalid Base"
	
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
			printPrompt(invalid_base)
		jr $ra
	
	
		
