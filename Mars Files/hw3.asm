#Homework #3
#Name : Aditya Balwani
#SBUID : 109353930
.data
	valid0: .byte '0'
	null: .byte '\n'
	validP0: .asciiz "+0"
	validN0: .asciiz "-0"
	valid1: .byte '1'
	valid2: .byte '2'
	valid3: .byte '3'
	valid4: .byte '4'
	valid5: .byte '5'
	valid6: .byte '6'
	valid7: .byte '7'
	valid8: .byte '8'
	valid9: .byte '9'
	validPlus: .ascii "+"
	validMinus: .ascii "-"
	validNaN:.asciiz "NaN\n"
	validPInf:.asciiz "+Inf\n"
	validNInf:.asciiz "-Inf\n"
	signPositive: .asciiz "Sign : 0 +\n"
	signNegative: .asciiz "Sign : 1 -\n"
	exponent: .asciiz "Exponent : "
	fraction: .asciiz "Fraction : "
	change: .byte '\0'
	.align 2
	temp: .float 0.0
	float0: .float 0
	float1: .float 1
	float2: .float 2
	float3: .float 3
	float4: .float 4
	float5: .float 5
	float6: .float 6
	float7: .float 7
	float8: .float 8
	float9: .float 9
	point: .byte '.'
	temp2: .space 32
	
	

.text
	toRadians:
		la $t0, pi
		l.s $f6, 0($t0)
		li $t0, 0x43340000
  		mtc1 $t0, $f5
  		div.s $f4,$f6,$f5
		mul.s $f0, $f12, $f4
		jr $ra
	
	arcLength:
		addi $sp, $sp, -4
  		sw $ra, 0($sp)
		jal toRadians
		mul.s $f0, $f0, $f13
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
	
	atof:
		addi $sp, $sp, -4
  		sw $ra, 0($sp)
		la $a1, validNaN
		jal compareStrings #Compare to NaN
		beqz $v0, isNaN
		la $a1, validPInf
		jal compareStrings #Compare to PInf
		beqz $v0, isPInf
		la $a1, validNInf
		jal compareStrings #Compare to NInf
		beqz $v0, isNInf
		
		li $t0, 0
		mtc1 $t0, $f4
		li $t7, 1
		add $t6, $zero, $a0
		lb $t0, ($t6)
		lb $t2, validMinus
		beq $t0, $t2, setNegative
		lb $t2, validPlus
		beq $t0, $t2, setPositive
				
		postMulNegative:
		loop1 :
			
			li $t1, 0x41200000
			mtc1 $t1, $f5
			mul.s $f4,$f4,$f5
			lb $t2, valid0
			beq $t0, $t2, isZero
			lb $t2, valid1
			beq $t0, $t2, isOne
			lb $t2, valid2
			beq $t0, $t2, isTwo
			lb $t2, valid3
			beq $t0, $t2, isThree
			lb $t2, valid4
			beq $t0, $t2, isFour
			lb $t2, valid5
			beq $t0, $t2, isFive
			lb $t2, valid6
			beq $t0, $t2, isSix
			lb $t2, valid7
			beq $t0, $t2, isSeven
			lb $t2, valid8
			beq $t0, $t2, isEight
			lb $t2, valid9
			beq $t0, $t2, isNine
			lb $t2, point
			beq $t0, $t2, prepLoop2
			j endLoop1
			isZero:
				la $t1, float0
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isOne:
				la $t1, float1
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isTwo:
				la $t1, float2
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isThree:
				la $t1, float3
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
				
			isFour:
				la $t1, float4
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isFive:
				la $t1, float5
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isSix:
				la $t1, float6
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isSeven:
				la $t1, float7
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isEight:
				la $t1, float8
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			isNine:
				la $t1, float9
				l.s $f5, 0($t1)
				add.s $f4,$f4,$f5
				j checkLoop
			checkLoop:
			addi $t6,$t6,1
			lb $t0, ($t6)
			beqz $t6, endLoop1
		j loop1
		
		prepLoop2:
			li $t0, 0
			mtc1 $t0, $f6
			addi $t6,$t6,1
			lb $t0, ($t6)
			li $t5, 0
			
		loop2:
			li $t1, 0x41200000
			mtc1 $t1, $f5
			mul.s $f6,$f6,$f5
			lb $t2, valid0
			beq $t0, $t2, isZero2
			lb $t2, valid1
			beq $t0, $t2, isOne2
			lb $t2, valid2
			beq $t0, $t2, isTwo2
			lb $t2, valid3
			beq $t0, $t2, isThree2
			lb $t2, valid4
			beq $t0, $t2, isFour2
			lb $t2, valid5
			beq $t0, $t2, isFive2
			lb $t2, valid6
			beq $t0, $t2, isSix2
			lb $t2, valid7
			beq $t0, $t2, isSeven2
			lb $t2, valid8
			beq $t0, $t2, isEight2
			lb $t2, valid9
			beq $t0, $t2, isNine2
			j endLoop2
			isZero2:
				la $t1, float0
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isOne2:
				la $t1, float1
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isTwo2:
				la $t1, float2
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isThree2:
				la $t1, float3
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
				
			isFour2:
				la $t1, float4
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isFive2:
				la $t1, float5
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isSix2:
				la $t1, float6
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isSeven2:
				la $t1, float7
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isEight2:
				la $t1, float8
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			isNine2:
				la $t1, float9
				l.s $f5, 0($t1)
				add.s $f6,$f6,$f5
				j checkLoop2
			checkLoop2:
			addi $t6,$t6,1
			lb $t0, ($t6)
			addi $t5, $t5, 1
			beqz $t6, endLoop2
		j loop2
			
		endLoop1:
			li $t1, 0x41200000
			mtc1 $t1, $f6
			div.s $f0, $f4, $f6 
			beqz $t7, mulNegative
			j endAtof
		
		endLoop2:
			li $t1, 0x41200000
			mtc1 $t1, $f7
			decimalLoop:
				beqz $t5, endDecLoop
				div.s $f6, $f6, $f7
				addi $t5, $t5, -1
				j decimalLoop
			endDecLoop:
			div.s $f0, $f4, $f7
			div.s $f6, $f6, $f7
			add.s $f0, $f0, $f6
			beqz $t7, mulNegative
			j endAtof
		
		isNaN:
			li $t0, 0x7fc00000
			mtc1 $t0, $f0
			j endAtof
		isPInf:
			li $t0, 0x7f800000
			mtc1 $t0, $f0
			j endAtof
		isNInf:
			li $t0, 0xff800000
			mtc1 $t0, $f0
			j endAtof
				
		setNegative:
			li $t7, 0
			addi $t6, $t6, 1
			lb $t0, ($t6)
			j postMulNegative
		setPositive:
			li $t7, 1
			addi $t6, $t6, 1
			lb $t0, ($t6)
			j postMulNegative
		mulNegative:
			li $t3, 0xbf800000
			mtc1 $t3, $f5
			mul.s $f0, $f0, $f5
			j endAtof
		endAtof:
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
	print_parts:
		addi $sp, $sp, -4
  		sw $ra, 0($sp)
		li $v0,2
		syscall
		li $v0, 11
		li $a0, '\n'
		syscall
		la $t0, temp
		mfc1 $t0, $f12
		li $t2, 0x7fc00000
		beq $t0, $t2, printNaN
		li $t2, 0x7f800000
		beq $t0, $t2, printPInf
		li $t2, 0xff800000
		beq $t0, $t2, printPInf
		andi $t1, $t0,0x80000000
		beqz $t1, printPosSign
		la $a0, signNegative
		li $v0, 4
		syscall
		j endSignPrint
		printPosSign:
			la $a0, signPositive
			li $v0, 4
			syscall
			j endSignPrint
			
		printNaN:
			la $a0, validNaN
			li $v0, 4
			syscall
			j endSignPrint
			
		printPInf:
			la $a0, validPInf
			li $v0, 4
			syscall
			j endSignPrint
		printNInf:
			la $a0, validNInf
			li $v0, 4
			syscall
			j endSignPrint
		endSignPrint:
		la $a0, exponent
		li $v0, 4
		syscall
		andi $t1, $t0, 0x7f800000 #Mask mantissa and Sign
		srl $t1, $t1, 23
		
		la $a0, ($t1)
		jal printExponent
		
		li $v0, 11
 		li $a0, '\t' 		
  		syscall
  		
  		la $a0, ($t1)
  		li $v0, 1
  		syscall
  		
		li $v0, 11
 		li $a0, '\n' 		
  		syscall
  		
  		la $a0, fraction
		li $v0, 4
		syscall
		
		andi $t1, $t0, 0x007fffff #Mask Sign and Exponent
		la $a0, ($t1)
		jal printFraction
		li $v0, 11
 		li $a0, '\t' 		
  		syscall
  		
  		la $a0, ($t1)
  		li $v0, 1
  		syscall
  		
		li $v0, 11
 		li $a0, '\n' 		
  		syscall
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
	print_binary_product:
		jr $ra
	
	arcLengthS:
		addi $sp, $sp, -4
  		sw $ra, 0($sp)
  		mov.s $f8, $f12
  		jal atof
  		mov.s $f12, $f8
  		mov.s $f13, $f0
  		jal arcLength
  		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra
		
	product:
		jr $ra	
	printExponent:
		add $t2, $zero,$a0
		li $t3, 0x00000080
		beqz $t2, noOnes
		shiftRightLoop:
			andi $t4, $t2, 0x00000001
			bnez $t4, oneFound
			srl $t2, $t2, 1
			srl $t3, $t3, 1
			j shiftRightLoop
		oneFound:
			and $t5, $t2, $t3
			beqz $t5, printZero
			li $v0, 11
 			li $a0, '1' 		
  			syscall
  			j incrementOneFoundLoop
			printZero:
				li $v0, 11
 				li $a0, '0' 		
  				syscall
  			incrementOneFoundLoop:
  			srl $t3,$t3,1
  			beqz $t3, endPrintExponent
  		j oneFound
  		noOnes:
  			li $v0, 11
 			li $a0, '0' 		
  			syscall
  		endPrintExponent:
  		jr $ra
  		
  	printFraction:
		add $t2, $zero,$a0
		li $t3, 0x00400000
		beqz $t2, noOnes
		shiftRightLoop2:
			andi $t4, $t2, 0x00000001
			bnez $t4, oneFound2
			srl $t2, $t2, 1
			srl $t3, $t3, 1
			j shiftRightLoop2
		oneFound2:
			and $t5, $t2, $t3
			beqz $t5, printZero2
			li $v0, 11
 			li $a0, '1' 		
  			syscall
  			j incrementOneFoundLoop2
			printZero2:
				li $v0, 11
 				li $a0, '0' 		
  				syscall
  			incrementOneFoundLoop2:
  			srl $t3,$t3,1
  			beqz $t3, endPrintExponent2
  		j oneFound2
  		noOnes2:
  			li $v0, 11
 			li $a0, '0' 		
  			syscall
  		endPrintExponent2:
  		jr $ra
  		
	compareStrings:
		add $t0, $zero, $zero
		add $t1, $zero, $a0
		add $t2, $zero, $a1
		compareLoop:
			lb $t3,($t1) #load a byte from each string
			lb $t4,($t2)
			beqz $t3,checkt2 #str1 end
			beqz $t4,missmatch
			slt $t5,$t3,$t4 #compare two bytes
			bnez $t5,missmatch
			addi $t1,$t1,1 #t1 points to the next byte of str1
			addi $t2,$t2,1
			j compareLoop
			
		missmatch:
			addi $v0, $zero, 1
			j endCompare
		checkt2:
			bnez $t4, missmatch
			add $v0, $zero, $zero
		endCompare:
			jr $ra
