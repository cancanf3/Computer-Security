
/* Author: Jose Pena
 * UCFID: 4142431
 * Tittle: CRC-15 x^15+x^13+x^6+x^4+x^1+1
 * Class: Computer Security
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void scanFile (char textChain[], char name[]);
unsigned xor(unsigned x, unsigned y );
unsigned crcCalc(char textChain[], unsigned poly);
unsigned crcVer(char textChain[], unsigned poly);
int cFlag, vFlag, opt;

int main (int argc, char* argv[]) {
	char textChain[504]; 
	unsigned poly = 0xA052;

	// Parsing the the flags
	while (( opt = getopt(argc, argv, "cv")) != -1) {
		switch (opt) {
			case 'c':
				cFlag = 1;
				break;
			case 'v':
				vFlag = 1;
				break;
			default: 
				printf("Usage: %s [-c calculates CRC] [-v verifies CRC] \n", argv[0]);
				exit(EXIT_FAILURE);

		}
	}

	scanFile(textChain, argv[2]);
	if (cFlag)
		crcCalc(textChain, poly);

	return 0;
}


void scanFile (char textChain[], char name[]) {
	FILE* file;
	file = fopen(name, "r");
	for (int i = 0; i < 504; i++)
		textChain[i] = 46;

	char aux;
	int i = 0;
	while (fscanf(file,"%c", &aux) != EOF && i < 504) {
		
		if (textChain[i] == 10 && textChain[i] == 13)
			continue;
		else if (textChain[i] < 32 || textChain[i] > 126) {
			printf("There is a special character not supported in the file. Program will exit\n");
			exit(EXIT_FAILURE);
		}
		else
			textChain[i++] = aux;

	}

	fclose(file);
}



unsigned xor(unsigned x, unsigned y ) {
	// printf("xor: %#010x\n\n", x^y);
	return x^y;
}

unsigned crcCalc(char textChain[], unsigned poly) {
	int count = 0;
	unsigned buffer;
	unsigned result;
	unsigned actualChar;
	int i = 0;
	printf("%c",textChain[count]);
	buffer = textChain[count++];
	printf("%c",textChain[count]);
	buffer = buffer << 8 | textChain[count++];
	printf("%c",textChain[count]);
	actualChar = textChain[count++];
	// printf("%#06x\n", buffer);
	do {
		if (buffer >= 0x8000) {
			// printf("\nXorting \n");
			result = xor(buffer, poly);
			buffer = result;
		}
		else {
			// printf("\nneeds more bit\n");
			// printf("actual char: %#010x\n", actualChar);
			buffer = (buffer << 1) + ((actualChar & (0x0080)) >> 7);
			actualChar = (actualChar & 0x007F) << 1;
			// printf("%#06x\n", buffer);
			if (actualChar == 0) {
				if (count % 64 == 0)
					printf(" - %#010x\n", result);
				printf("%c",textChain[count]);
				// printf("pide new char %#06x\n",textChain[count]);
				actualChar = textChain[count++];

			}
		}
		i++;
	}while( count < 504);
	printf("%#010x\n", result);

	return result;
}

unsigned crcVer(char textChain[], unsigned poly) {
	return 0;
}