/*
 * Author: Jose Pena
 * Computer Security
 * HillCipher
 */

	// FILE *keyFile;
	// keyFile = fopen(fileName, "r");
	// int length; 
	// fscanf(keyFile, "%d", &length);
	// int** key = (int **)malloc(length * sizeof(int));
	// int i, j;
	// for ( i = 0 ; i < length ; i++)
	// 	key[i] = (int *)malloc(length * sizeof(int));

	// for ( i = 0 ; i < length ; i++)
	// 	for ( j = 0 ; j < length ; j++)
	// 		fscanf(keyFile, "%d", key[i][j]);



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int intParser ( int letter );
char* fileReader ( char* fileName, int keyLength, int* length );
int mod26 ( int letter );



int main ( int argc, char* argv[] ) {

	FILE *keyFile;
	keyFile = fopen(argv[1], "r");

	// Reading the key 
	int length; 
	fscanf(keyFile, "%d", &length);
	int key[length][length];
	for ( int i = 0 ; i < length ; i++)
		for ( int j = 0 ; j < length ; j++)
			fscanf(keyFile, "%d", &(key[i][j]));

	printf("key Matrix: \n\n\n");
	for ( int i = 0 ; i < length ; i++) {
		for ( int j = 0 ; j < length ; j++) {
			printf("%d ", key[i][j]);
		}
		printf("\n");
	}
	// Reading the Plain Text
	int pl = 0;
	char* plainText = fileReader(argv[2], length, &pl);
	printf("\nPlainText: \n\n%s\n", plainText);

	// Enctryption
	char *cypher = (char *)malloc(sizeof(char)*10000);
	int w = 0;

	for ( int z = 0 ;  z < pl ; z += length ) {		
		for (int i = 0 ; i < length ;  i++) {
			int aux = 0;
			for(int j = 0 ; j < length ; j++) {
				aux += key[i][j] * (plainText[z+j]-97);
			}
			cypher[w++] = (aux%26)+97;
		}
	}

	printf("\n Cypher Text: \n\n\n%s\n",cypher);
	fclose(keyFile);
	free(plainText);
	free(cypher);

	return 0;

}


// Check if it is letter and convert upper case to lower case
int intParser ( int letter ) {
	// special Character
	if ( letter < 65 || letter > 122 || 
		(letter > 90 && letter < 97 ))
		return 0;

	// Upper Case 
	if ( letter > 64 && letter < 91 )
		return letter + 32;

	return letter;
}


// Read the file 
char* fileReader ( char* fileName, int keyLength, int* length ) {
	FILE *plainText;
	plainText = fopen(fileName, "r");
	char *buffer = (char *)malloc(sizeof(char)*10000);
	int i;
	char aux;

	// Cleaning the buffer
	for ( i = 0; i < 10000 ; i++ )
		buffer[i] = '\0';

	
	// Reading from the file;
	i = 0;
	while ( fscanf(plainText, "%c", &aux) != EOF )
		if (intParser(aux) == 0)
			continue;
		else 
			buffer[i++] = intParser(aux);

	//padding
	int numberPads = keyLength - (i % keyLength);
	for (int j = 0 ; j < numberPads ; j++)
		buffer[i++] = 'x';
	
	fclose(plainText);
	*length = i;

	return buffer;
}
