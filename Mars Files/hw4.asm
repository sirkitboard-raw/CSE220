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
		
		jr $ra
	
	
		