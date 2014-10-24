/*Aditya Balwani
SBUID: 109353920*/
#include <stdlib.h>
#include <stdio.h>

/* Function prototypes*/
int promptForId(void);
int scrambleId(int id);
int xor(int v, int id);
int shift(int v, int n);
int printResults(int original, int scrambled);

/* Ask the user for their SBUID*/
int promptForId(void) {
	int id=0;
	int valid=0;
	char line[256];
	/* Loop until valid input is given*/
	do {
		printf("Please enter your SBUID: ");
		/* Read in the whole line*/

		fgets(line, sizeof(line), stdin);
		/* If we were not able to parse the string, tell the user*/
		if(!(valid = sscanf(line, "%d", &id))) {
			printf("Invalid id entered.\n");
		}
	} while(!valid);
	return id;
}

/* Scramble the SBUID*/
int scrambleId(int id) {
	int scrambled=0;
	int i=0;
	int r=0;
	int rounds=0;
	scrambled = id;
	srand(id);
	r = rand();
	/* Bound this random number between 1-10*/
	rounds = (rand() % 10) + 1;
	printf("Performing %d rounds of shifting and xoring.\n", rounds);
	/* Go through some crazy shifting operations*/
	for(i = 0; i < rounds; i++){
		scrambled = shift(scrambled, r >>= 1);
	}
	return scrambled;
}

/* Perform bitwise XOR on the SBU ID*/
int xor(int v, int id) {
	int result;
	result = v ^ id;
	return result;
}

/* Shift the value right and xor*/
int shift(int v, int r) {
	int result=0;
	int shamt = 0x08000000;
	while(shamt) {
		result += xor(v, r); /* add the return value of xor to result*/
		shamt = shamt >> 1; /* Shift right by 1 */
	}
	return result;
}

int printResults(int original, int scrambled) {
	/* If the scrambled number is even*/
	int isEven=0;
	printf("%d -> %d\n", original, scrambled);
	isEven = scrambled % 2;
	if(isEven == 0){
		printf("The scrambled result is even!\n");
		return 0;
	}
	/* else it is odd*/
	printf("The scrambled result is odd!\n");
	return 127;
}

/* The program starts here*/
int main() {
	int id=0;
	int scrambled=0;
	int result=0;
	id = promptForId();
	printf("SBUID: %d\n", id);
	/* Scramble the SBUID*/
	scrambled = scrambleId(id);
	/* Print out the scrambled value*/
	result = printResults(id, scrambled);
	return result;
}

/* @@GDB_OUTPUT_HERE@@
bash-3.2$ gdb a.out
GNU gdb (GDB) 7.8
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "sparc-sun-solaris2.10".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from a.out...done.
(gdb) clear
No source file specified.
(gdb) break 23
Breakpoint 1 at 0x10c10: file hw5.c, line 23.
(gdb) break 44
Breakpoint 2 at 0x10d10: file hw5.c, line 44.
(gdb) break 52
Breakpoint 3 at 0x10d6c: file hw5.c, line 52.
(gdb) run
Starting program: /export/home1/a/b/abalwani/cse220C/a.out
[Thread debugging using libthread_db enabled]
[New Thread 1 (LWP 1)]
Please enter your SBUID: 109353920
[Switching to Thread 1 (LWP 1)]

Breakpoint 1, promptForId () at hw5.c:23
23                      if(!(valid = sscanf(line, "%d", &id))) {
(gdb) print line
$1 = "109353920\n", '\000' <repeats 46 times>, "\377\377\377\377\377\377\377\377\377:\000\000\377\277\373p\377:@L\000\000\000\f\000\001\000\064\377\277\377\320\377\377\377\377\000\000\000\000\377\277\374\\\000\000\000\002\377\377\377\377\377\377\377\377\377\277\373x\377:X\350\000\000\000\000\000\000\000\000\377\277\374\264\000\000\000\000\000\000\000\001\000\001\005\v\377\067\np\377 \267\200\000\001\005\v\377\067\004 \377\067\004 \000\000\000\002\006\212\317\004\000\000\000\021\000\001\003L\025\001\377\377\000\001\000\000\000\000\000\000\000\000\000\002\377\277\373p"...
(gdb) continue
Continuing.
SBUID: 109353920
Performing 4 rounds of shifting and xoring.

Breakpoint 2, scrambleId (id=109353920) at hw5.c:44
44                      scrambled = shift(scrambled, r >>= 1);
(gdb) print i
$2 = 0
(gdb) continue
Continuing.

Breakpoint 3, xor (v=109353920, id=12853) at hw5.c:52
52              result = v ^ id;
(gdb) backtrace
#0  xor (v=109353920, id=12853) at hw5.c:52
#1  0x00010dbc in shift (v=109353920, r=12853) at hw5.c:61
#2  0x00010d2c in scrambleId (id=109353920) at hw5.c:44
#3  0x00010ec4 in main () at hw5.c:89
(gdb) info frame
Stack level 0, frame at 0xffbffab0:
 pc = 0x10d6c in xor (hw5.c:52); saved pc = 0x10dbc
 called by frame at 0xffbffb18
 source language c.
 Arglist at 0xffbffab0, args: v=109353920, id=12853
 Locals at 0xffbffab0, Previous frame's sp in fp
 Saved registers:
  l0 at 0xffbffab0, l1 at 0xffbffab4, l2 at 0xffbffab8, l3 at 0xffbffabc, l4 at 0xffbffac0, l5 at 0xffbffac4, l6 at 0xffbffac8,
  l7 at 0xffbffacc, i0 at 0xffbffad0, i1 at 0xffbffad4, i2 at 0xffbffad8, i3 at 0xffbffadc, i4 at 0xffbffae0, i5 at 0xffbffae4,
  fp at 0xffbffae8, i7 at 0xffbffaec
(gdb) clear xor
Deleted breakpoint 3
(gdb) continue
Continuing.

Breakpoint 2, scrambleId (id=109353920) at hw5.c:44
44                      scrambled = shift(scrambled, r >>= 1);
(gdb) print i
$3 = 1
(gdb) continue
Continuing.

Breakpoint 2, scrambleId (id=109353920) at hw5.c:44
44                      scrambled = shift(scrambled, r >>= 1);
(gdb) print i
$4 = 2
(gdb) continue
Continuing.

Breakpoint 2, scrambleId (id=109353920) at hw5.c:44
44                      scrambled = shift(scrambled, r >>= 1);
(gdb) print i
$5 = 3
(gdb) continue
Continuing.
109353920 -> 1000537112
The scrambled result is even!
[Inferior 1 (process 13561    ) exited normally]
(gdb) quit

@@GDB_OUTPUT_HERE@@ */
