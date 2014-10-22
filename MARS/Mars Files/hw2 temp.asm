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
	
	j while
		
	#---------------------------------------------------------------------------
	#---------------------------Convert UTF8 to UTF16BE-------------------------
	#---------------------------------------------------------------------------
	utf816be:
		la $a0, fileName
		li $a1, 0
		li $v0, 13
		syscall 
		
		move $t0, $v0
		
		la $a0, fileOutName
		li $a1, 1
		li $v0, 13
		syscall
		
		move $t5, $v0
		
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
			beqz $t2, numBytes4
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
			
			move $a0, $t5
			la $a1, ($t1)
			li $a2, 2
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
			
			move $a0, $t5
			la $a1, ($t1)
			li $a2, 2
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
			
			andi $t1,$t1,0x1F
			andi $t2, $t2, 0x3F
			andi $t3, $t3, 0x3F
			
			sll $t1, $t1, 12
			sll $t2, $t2, 6
			or $t1, $t1, $t2
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
			
			move $a0, $t5
			la $a1, ($t1)
			li $a2, 2
			li $v0, 15
			syscall
			
		j readFileBE
			
		numBytes4:
			la $a0, num4byte
			li $v0, 4
			syscall
			
		j readFileBE
		
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
	invalid: .asciiz "Invalid Choice\n"
	fileName: .asciiz "in.txt"
	fileOutName: .asciiz "out.txt"
	validString: .asciiz "The file is valid\n"
	invalidString: .asciiz "The file is invalid\n"
	codePointPrefix: .asciiz "U+"
	num1byte: .asciiz "1 Byte "
	num2byte: .asciiz "2 Byte "
	num3byte: .asciiz "3 Byte"
	num4byte: .asciiz "4 Byte"
	buf: .space 3
