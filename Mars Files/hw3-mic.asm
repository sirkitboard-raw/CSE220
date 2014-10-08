# Homework #3
# name: Michelle Chan
# sbuid: 109303129
.data
rad: .float 180
ften: .float 10
newline: .asciiz "\n"
space: .asciiz " "
sign: .asciiz "Sign: "
exponent: .asciiz "Exponent: "
fraction: .asciiz "Fraction: "
binary: .asciiz "Binary Product: "
pos: .asciiz "0 +\n"
neg: .asciiz "1 -\n"
null: .asciiz ""
ten: .word 10
test: .float -3


.text
######################################################### PART 1 ###########################################################################
toRadians: 
	l.s $f4, pi 
	l.s $f5, rad		#load 180 to $t0
	div.s $f4, $f4, $f5	# pi/180
	mul.s $f0, $f4, $f12	# degree * pi/180
	jr $ra


arcLength:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	mul.s $f0, $f4, $f13	# rad * radius
	lw $ra, 0($sp)
	addi $sp $sp 4
	jr $ra
######################################################## PART 2 ############################################################################
atof:
	move $t1, $a0 #load string to temp
nextchar:	
	lb $t0,($t1)	    # get byte from string
	li $t2, 0x0000000A
       beq $t0, $t2, end	#if no more, go to end
       addi $t1, $t1,1	#move pointer to next
       li $t2, 0x0000000A
       beq $t0, $t2, end
       #li $t3, 46		#load .
       #la $t3, pos
       #beq $t0, $t3, plus
       #la $t3, neg
       #beq $t0, $t3, minus
       #beq $t3, $t0, decimal	#if number has a  decimal 
check:
	li $t3, 48
       sub $t4, $t0, $t3
       li $t3, 9
       ble $t4, $t3, end
continue:
      # ble $t4, $t3, less
	mtc1 $t4, $f4
	cvt.s.w $f4, $f4
	add.s $f5, $f4, $f5
	l.s $f6, ften
	mul.s $f5, $f5, $f6
	lb $t0,($t1)
	li $t3, 48
       sub $t4, $t0, $t3
       li $t3, 9
       ble $t4, $t3, end
	mtc1 $t0, $f4
	cvt.s.w $f4, $f4
	add.s $f5,$f4, $f5
      j nextchar

#plus: 
	
#minus:

less:
	#bgtz $t4, keep
	bgtz $t4, keep
	j end

keep:
        add $t6, $t4, $t6 #add valid number to t6
	addi $t1, $t1,1 #check if there are more in the string
	lb $t0,($t1)	    # get byte from string
	li $t2, 0x0000000A
       # beq $t0, $t2, tofloat	#if no next, go to valid
	
        la $t5, ten	#multiply by 10
        mul $t6, $t5, $t6
        j nextchar
	
#valid:
#	mtc1 $t4, $f0
#	cvt.s.w $f0, $f0
#	addi $t1, $t1, 1
#	j nextchar
end:
	mov.s $f12, $f0
	li $v0, 2
	syscall
	jr $ra
	
print_parts:
	la $a0, sign
	li $v0, 4
	syscall
	
	mtc1 $t0, $f12 #move back to gp
	l.s $f13, test
	mtc1 $t0,$f13
	bgtz $t0, positive
	bltz $t0, negative
	j printExponent
negative: 
	la $a0, sign
	li $v0, 4
	la $a0, neg
	li $v0, 4
	syscall
	j printExponent
positive:
	la $a0, sign
	li $v0, 4
	la $a0, pos
	li $v0, 4
	syscall
	j printExponent
	
printExponent:
	and $t1, $t1, $t0 #mask 8bits of exponent
	srl $t1, $t1, 4
	srl $t1, $t1, 2
	srl $t1, $t1, 1
	srl $t1,$t1, 0
	
	la $a0, exponent #print exponent
	li $v0, 4
	syscall
	move $t1, $a0 #move masked and shifted to a0
	li $v0, 35 #prints a0
	la $a0, space #print space
	li $v0, 4
	move $t1, $a0
	li $v0, 1
	syscall
	la $a0, newline
	li $v0, 1
	syscall
	
	la $a0, fraction
	li $v0, 4
	syscall

	jr $ra	 

print_binary_product:
	#mtc1 
	jr $ra

arcLengthS:
	jal atof
	mov.s $f6, $f13
	jal arcLength
	jr $ra
	
product:
	move $t0, $a0 #move counter to temp 0
	li $t1, 1
	blt $t0, $t1, lessresult
	li $t2, 0x3f800000
	mtc1 $t2, $f0
	productloop:
		lw $t2,0($sp)
		addi $sp, $sp, 4
		mtc1 $t2, $f4
		mul.s $f0,$f0,$f4
		beqz $t0, result
		addi $t0, $t0, -1
		j productloop

	
lessresult:
	li $t1, 0
result: 
	jr $ra
