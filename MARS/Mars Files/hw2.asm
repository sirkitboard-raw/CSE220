# Homework #2
#name: Aditya Balwani
#sbuid: 109353920
.text
.globl main
main:
	#---------------------------------------------------------------------------
	#-------------------------------Start Loop----------------------------------
	#---------------------------------------------------------------------------
	while:
		la $a0, mainMenu
		li $v0, 4
		syscall
		
		li $v0, 5
		syscall
		move $t0,$v0
		
		la $a0, inputFile
		li $v0, 4
		syscall
		
		la $a0, inputBuffer
		li $a1, 20
		li $v0, 8
		syscall
	#---------------------------------------------------------------------------
	#-------------------------Remove Extra Line from Input----------------------
	#---------------------------------------------------------------------------
		li $t0, 0
		la $s0, inputBuffer
		lb $t1, ($s0)
		loop1 :
			addi $t0,$t0,1
			addi $s0, $s0, 1
			lb $t1, ($s0)
			beqz $t1, exit1
		j loop1
		exit1:
			la $t2, inputBuffer
			add $t2, $t2, $t0
			addi $t2, $t2, -1
			lb $t3, change
			sb $t3, 0($t2)
		
		la $a0, inputBuffer
		li $v0, 4
		syscall
		
		
		la $a0, outputFile
		li $v0, 4
		syscall
		
		la $a0, outputBuffer
		li $a1, 20
		li $v0, 8
		syscall
		
		li $t0, 0
		la $s0, outputBuffer
		lb $t1, ($s0)
		loop2 :
			addi $t0,$t0,1
			addi $s0, $s0, 1
			lb $t1, ($s0)
			beqz $t1, exit2
		j loop2
		exit2:
			la $t2, outputBuffer
			add $t2, $t2, $t0
			addi $t2, $t2, -1
			lb $t3, change
			sb $t3, 0($t2)
			
		la $a0, outputBuffer
		li $v0, 4
		syscall
		
		la $a0, newline
		li $v0, 4
		syscall
		
		li $t1, 1
		li $t2, 2
		li $t3, 3
		beq $t0,$t1,utf816le    #Convert 8 to 16LE
		beq $t0,$t2,utf816be    #Convert 8 to 16BE
		beq $t0,$t3,exit        #Exit
	#---------------------------------------------------------------------------
	#---------------------------Convert UTF8 to UTF16LE-------------------------
	#---------------------------------------------------------------------------
	utf816le:
		la $a0, inputBuffer
		li $a1, 0
		li $v0, 13
		syscall 
		
		move $t0, $v0

		bgtz $t0, readBOMLE
		j exit
		
		readBOMLE:
			
			move $a0, $t0
			la $a1, buf
			li $a2, 3
			li $v0, 14
			syscall
			
			beqz $v0, closeFile
			
			
			
			la $s0, buf
			lbu $t1, 0($s0)
			sll $t1,$t1,8
			lbu $t2, 1($s0)
			or $t1,$t1,$t2
			sll $t1,$t1,8
			lbu $t2, 2($s0)
			or $t1, $t1, $t2
			
			li $t3, 0xefbbbf
			beq $t1, $t3, fileValidLE
			
			j invalidFile
			
		j closeFile
		
		fileValidLE: 
			la $a0, validString
			li $v0, 4
			syscall
			
			la $a0, outputBuffer
			li $a1, 1
			li $a2, 0
			li $v0, 13
			syscall
			move $t5, $v0
			
			la $t2, utf16lebom 
			move $a0, $t5
			la $a1, ($t2)
			li $a2, 2
			li $v0, 15
			syscall
			
		
		readFileLE:
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
			bltz $v0, invalidFile
		
			la $s0, buf
			lbu $t1, 0($s0)
			andi $t2,$t1,0x80
			beqz $t2, numBytes1LE
			andi $t2, $t1, 0xE0
			li $t3, 0xC0
			beq $t2, $t3, numBytes2LE
			andi $t2, $t1, 0xF0
			li $t3, 0xE0
			beq $t2, $t3, numBytes3LE
			andi $t2, $t1, 0xF8
			li $t3, 0xF0 
			beq $t2, $t3, numBytes4LE
			
			j invalidFile
		j readFileLE
		
		numBytes1LE:
			la $a0, num1byte
			li $v0, 4
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
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			
			sb $t1,outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
			srl $t1, $t1, 8
			sb $t1, outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileLE
			
		numBytes2LE:
			la $a0, num2byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
		
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x1F
			andi $t2, $t2, 0x3F
			
			sll $t1, $t1, 6
			or $t1, $t1, $t2
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			sb $t1,outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
			srl $t1, $t1, 8
			sb $t1, outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileLE
			
		numBytes3LE:
			la $a0, num3byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
			la $s0, buf
			lbu $t3, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t3)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x0F
			andi $t2, $t2, 0x3F
			andi $t3, $t3, 0x3F
			
			sll $t1, $t1, 6
			or $t1, $t1, $t2
			sll $t1, $t1, 6
			or $t1, $t1, $t3
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			sb $t1,outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
			srl $t1, $t1, 8
			sb $t1, outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileLE
			
		numBytes4LE:
			la $a0, num4byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
			
			la $s0, buf
			lbu $t3, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			blez $v0, invalidFile
			
			la $s0, buf
			lbu $t4, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t3)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t4)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x07
			andi $t2, $t2, 0x3F
			andi $t3, $t3, 0x3F
			andi $t4, $t4, 0x3F
			
			sll $t1, $t1, 18
			sll $t2, $t2, 12
			sll $t3,$t3, 6
			or $t1, $t1, $t2
			or $t1, $t1, $t3
			or $t1,$t1,$t4
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			li $t6, 0x10000
			sub $t1, $t1, $t6
			srl $t2, $t1, 10
			andi $t1, $t1, 0x3FF
			add $t1, $t2, $t1
			addi $t2,$t2,0xDC00
			addi $t1,$t2,0xD800
			
			la $a0, newline
			li $v0, 4
			syscall
			
			
			sb $t1,outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
			srl $t1, $t1, 8
			sb $t1, outbuf
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
		j readFileLE
	j while
		
	#---------------------------------------------------------------------------
	#---------------------------Convert UTF8 to UTF16BE-------------------------
	#---------------------------------------------------------------------------
	utf816be:
		la $a0, inputBuffer
		li $a1, 0
		li $v0, 13
		syscall 
		
		move $t0, $v0

		bgtz $t0, readBOMBE
		j exit
		
		readBOMBE:
			
			move $a0, $t0
			la $a1, buf
			li $a2, 3
			li $v0, 14
			syscall
			
			beqz $v0, closeFile
			
			
			
			la $s0, buf
			lbu $t1, 0($s0)
			sll $t1,$t1,8
			lbu $t2, 1($s0)
			or $t1,$t1,$t2
			sll $t1,$t1,8
			lbu $t2, 2($s0)
			or $t1, $t1, $t2
			
			li $t3, 0xefbbbf
			beq $t1, $t3, fileValidBE
			
			la $a0, invalidString
			li $v0, 4
			syscall
			
		j closeFile
		
		fileValidBE: 
			la $a0, validString
			li $v0, 4
			syscall
			
			la $a0, outputBuffer
			li $a1, 1
			li $a2, 0
			li $v0, 13
			syscall
			move $t5, $v0
			
			la $t2, utf16bebom 
			move $a0, $t5
			la $a1, ($t2)
			li $a2, 2
			li $v0, 15
			syscall
			
		
		readFileBE:
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
		
			la $s0, buf
			lbu $t1, 0($s0)
			andi $t2,$t1,0x80
			beqz $t2, numBytes1
			andi $t2, $t1, 0xE0
			li $t3, 0xC0
			beq $t2, $t3, numBytes2
			andi $t2, $t1, 0xF0
			li $t3, 0xE0
			beq $t2, $t3, numBytes3
			andi $t2, $t1, 0xF8
			li $t3, 0xF0 
			beq $t2, $t3, numBytes4
			
			j invalidFile
		j readFileBE
		
		numBytes1:
			la $a0, num1byte
			li $v0, 4
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
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			sb $t1, outbuf
			srl $t1, $t1, 8
			sb $t1, outbuf2
			move $a0, $t5
			la $a1, outbuf2
			li $a2, 1
			li $v0, 15
			syscall
			
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileBE
			
		numBytes2:
			la $a0, num2byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
		
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x1F
			andi $t2, $t2, 0x3F
			
			sll $t1, $t1, 6
			or $t1, $t1, $t2
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			sb $t1, outbuf
			srl $t1, $t1, 8
			sb $t1, outbuf2
			move $a0, $t5
			la $a1, outbuf2
			li $a2, 1
			li $v0, 15
			syscall
			
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileBE
			
		numBytes3:
			la $a0, num3byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
			la $s0, buf
			lbu $t3, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t3)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x0F
			andi $t2, $t2, 0x3F
			andi $t3, $t3, 0x3F
			
			sll $t1, $t1, 6
			or $t1, $t1, $t2
			sll $t1, $t1, 6
			or $t1, $t1, $t3
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, newline
			li $v0, 4
			syscall
			
			sb $t1, outbuf
			srl $t1, $t1, 8
			sb $t1, outbuf2
			move $a0, $t5
			la $a1, outbuf2
			li $a2, 1
			li $v0, 15
			syscall
			
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileBE
			
		numBytes4:
			la $a0, num4byte
			li $v0, 4
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
		
			la $s0, buf
			lbu $t2, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
			
			la $s0, buf
			lbu $t3, 0($s0)
			
			move $a0, $t0
			la $a1, buf
			li $a2, 1
			li $v0, 14
			syscall
		
			beqz $v0, closeFile
			
			la $s0, buf
			lbu $t4, 0($s0)
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t2)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t3)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			la $a0, ($t4)
			li $v0, 34
			syscall
			
			la $a0, tab
			li $v0, 4
			syscall
			
			andi $t1,$t1,0x07
			andi $t2, $t2, 0x3F
			andi $t3, $t3, 0x3F
			andi $t4, $t4, 0x3F
			
			sll $t1, $t1, 18
			sll $t2, $t2, 12
			sll $t3,$t3, 6
			or $t1, $t1, $t2
			or $t1, $t1, $t3
			or $t1,$t1,$t4
			
			la $a0, codePointPrefix
			li $v0, 4
			syscall
			
			la $a0, ($t1)
			li $v0, 34
			syscall
			
			li $t6, 0x10000
			sub $t1, $t1, $t6
			srl $t2, $t1, 10
			andi $t1, $t1, 0x3FF
			add $t1, $t2, $t1
			addi $t2,$t2,0xDC00
			addi $t1,$t2,0xD800
			
			la $a0, newline
			li $v0, 4
			syscall
			
			
			sb $t1, outbuf
			srl $t1, $t1, 8
			sb $t1, outbuf2
			move $a0, $t5
			la $a1, outbuf2
			li $a2, 1
			li $v0, 15
			syscall
			
			move $a0, $t5
			la $a1, outbuf
			li $a2, 1
			li $v0, 15
			syscall
			
		j readFileBE
		
	invalidFile:
		la $a0, invalidString
		li $v0, 4
		syscall
	closeFile:
		move $a0, $t0
		li $v0, 16
		syscall
		
		move $a0, $t5
		li $v0, 16
		syscall
	j while
	
	#---------------------------------------------------------------------------
	#----------------------------------Exit-------------------------------------
	#---------------------------------------------------------------------------
	exit:
		li $v0, 10
		syscall
		
	
	
.data
	mainMenu: .asciiz "\n=== UTF Converter === \n\n1. Encode UTF-8 -> UTF16-LE \n2. Encode UTF-8 -> UTF16-BE \n3. Exit\n"
	newline: .asciiz "\n"
	tab: .asciiz "\t"
	a: .word 1
	change: .byte '\0'
	inputFile: .asciiz "Please enter the path to the input file : "
	outputFile: .asciiz "Please enter a path for a new file : "
	validString: .asciiz "The file is valid\n"
	invalidString: .asciiz "The file is invalid\n"
	codePointPrefix: .asciiz "U+"
	num1byte: .asciiz "1 Byte "
	num2byte: .asciiz "2 Byte "
	num3byte: .asciiz "3 Byte"
	utf8bom: .word 0xBFBBEF
	utf16lebom: .word 0xFEFF
	utf16bebom: .word 0xFFFE
	num4byte: .asciiz "4 Byte"
	buf: .space 3
	outbuf: .space 1
	inputBuffer: .space 20
	outputBuffer: .space 20
	outbuf2: .space 1
	temp: .asciiz "Memory"
	