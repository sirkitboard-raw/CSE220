#Homework 1
#name: Halaa_Menasy
#SBU ID: 109316248

.text
.globl main
main:

li $v0,4
la $a0, user_prompt                 #asks the user for input
syscall

li $v0, 8
la $a0, file_name                  # reads in string name of textfile
li $a1, 50         
syscall
move $t0,$a0,                      #move the address in $a0 to $t0 file name is in t0


li $s0, 0
li $t9, '\n'                      #loads new line for future comparison

remove:
lb $t0, file_name($s0)           # $t0 contains current char
beq $t0, $t9, replace            # found newline character
beq $t0, $0, done                # found a null, we're done
addi $s0, $s0, 1
j remove

replace:
la $t1, file_name($s0)
sb $0, ($t1)                #replaces newline with null

done:
li $v0, 13
la $a0, file_name		#open file
li $a1,0
li $a2,0
syscall

bgez $v0,success		#if v0 is greater than 0 continue with progam

li $v0, 4
la $a0, error_message_file      #else display error message
syscall

j main				#reprompt

success:
move $a0, $v0			#file descriptor in $v0 moved to a0
move $s2, $v0			#loads whats in buffer into s2


bom_check:			#check first 3 bytes for proper BOM
li $v0, 14
la $a1, bom_buffer		#a2 maximum number of characters read which is 1
li $a2, 1
syscall


li $t1, 0xFFFFFFEF		   #loads 1 of 3 BOM bytes to compare to file
lb $t4, ($a1)			   #bytes from file
beq $t4, $t1, bom_byte_2

la $a0, error_message_bom
li $v0, 4
syscall

j main

bom_byte_2:			#loads 2  of 3 BOM bytes to compare to file
li $v0, 14
la $a1, bom_buffer		#a2 maximum number of characters read which is 1
li $a2, 1
syscall

li $t1, 0xFFFFFFBB		#compares BOM to proper byte
lb $t4, ($a1)			#continue to byte 3 if right, else error message
beq $t4, $t1, bom_byte_3

la $a0, error_message_bom
li $v0, 4
syscall

j main

bom_byte_3:			#loads 3 of 3 BOM bytes to compare to file
li $v0, 14
la $a1, bom_buffer		#a2 maximum number of characters read which is 1
li $a2, 1
syscall

li $t1, 0xFFFFFFBF
lb $t4, ($a1)
beq $t4, $t1, loop

la $a0, error_message_bom
li $v0, 4
syscall
j main

loop:
move $a0, $s2                       #move file descripter from s2 to a0
li $v0, 14
la $a1, bom_buffer		    #read 1 byte
li $a2, 1
syscall

beqz $v0, exit                      #if v0 equals zero, file is done, contiue

continue: 
li $v0, 14           
andi $t3, ($a1) , 0x80               #mask last 7 bits 
beqz $t3, one_byte  
                                     #if t3 (the first bite) is equal to 0 go to one byte instructions



j two_bytes			#else go to two byte instructions

one_byte:

la $a0, one_b			#print one byte message
li $v0, 4
syscall

lb $s2, ($a1)			#print hex in whatever is in $s2
li $v0, 34
syscall

la $a0, u+			#print u+
li $v0 4
syscall

lb $a0, ($a1)			#print hex again
li $v0, 34
syscall

la $a0, newLine			#print new line
li $v0, 4
syscall

j loop

two_byte:
andi $t5, $s2, 0xe0             #mask last 76bits 
move $a0, $t4			#t5 second bit, ($t3 has first. just a reminder)
beqz $t4, three_byte

sll $t7,$t3,6                    #shift left whats in t3 
or $t3, $t7,$t3

la $a0, two_b			#print two byte message
li $v0, 4
syscall

lb $a0, ($t4)			#print hex again
li $v0, 34
syscall

la $a0, u+			#print u+
li $v0 4
syscall

lb $a0, ($t4)			#print hex again
li $v0, 34
syscall

j loop

three_byte:



four_byte:




exit:
li $v0, 10
syscall

.data
user_prompt: .asciiz "\nEnter the path to the input file  "
file_name: .space 50
error_message_file: .asciiz "You entered an invalid file path" 
buffer: .space 1
bom_buffer: .space 1
error_message_bom: .asciiz "Incorrect BOM , try a different file"
bom_success: .asciiz "BOM is correct"
newLine: .asciiz "\n"
one_b: .asciiz "one byte   "
two_b: .asciiz "two byte"
three_b: .asciiz "three byte"
four_b: .asciiz "four byte"
u+: .aciiz"    U+"
