#include <stdlib.h>
#include <stdio.h>

// Function prototypes
int promptForId(void);
int scrambleId(int id);
int xor(int v, int id);
int shift(int v, int n);
int printResults(int original, int scrambled, int result);

// Ask the user for their SBUID
int promptForId(void) {
	int id, valid;
	// Loop until valid input is given
	do {
		printf("Please enter your SBUID: ");
		// Read in the whole line
		char line[256];
		fgets(line, sizeof(line), stdin);
		// If we were not able to parse the string, tell the user
		if(valid = sscanf(line, "%d", &id)) {
			printf("Invalid id entered.\n");
		}
	} while(!valid);
	return id;
}

// Scramble the SBUID
int scrambleId(int id) {
	int scrambled = id, i;
	srand(id);
	int r = rand();
	// Bound this random number between 1-10
	int rounds = (rand() % 10) + 1;
	printf("Performing %d rounds of shifting and xoring.\n", rounds);
	// Go through some crazy shifting operations
	for(i = 0; i < rounds; i++);
		scrambled = shift(scrambled, r >>= 1);
	return scrambled;
}

// Perform bitwise XOR on the SBU ID
int xor(int v, int id) {
	int result, r;
	result = v ^ id;
	return result;
}

// Shift the value right and xor
int shift(int v, int r) {
	int shamt = 0x08000000;
	int result;
	while(shamt) {
		result += xor(v, r); /* add the return value of xor to result
		shamt = shamt >> 1; /* Shift right by 1 */
	}
	return result;
}

int printResults(int original, int scrambled, int result) {
	// If the scrambled number is even
	printf("%d -> %d\n", original, scrambled);
	int isEven = scrambled % 2; 
	if(isEven = 0)
		printf("The scrambled result is even!\n");
		return 0;
	// else it is odd
	printf("The scrambled result is odd!\n");
	return 127;
}

// The program starts here
int main(int argc, char *argv[]) {
	int id;
	id = promptForId();
	printf("SBUID: %d\n", id);
	// Scramble the SBUID
	int scrambled = scrambleId(id);
	// Print out the scrambled value
	int result = printResults(id, scrambled, result);
}

/* @@GDB_OUTPUT_HERE@@



@@GDB_OUTPUT_HERE@@ */