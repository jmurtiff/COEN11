/******************************************************************/
/* Jordan Murtiff						  */
/* Encryption Project					 	  */
/* Date: December 5, 2017				          */
/*							  	  */
/* This program is an encryption/decryption program that is able  */
/* to rewrite data from text or binary files using bitwise        */
/* operators and encrypt or decrypt a file using a specifc key.   */
/* The key is a number from 0-255 that is then used to decrypt the*/
/* file once encrypted.				                  */		

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
	//Varaible used for the for loop.
	int i;
	
	//Return value of fread that is then used to fwrite the encrypted/decryped characters into a file.
	int ret;

	//Changes the key (number entered from 0-255) in to a variable.
	char* key = argv[1];

	//Change the key from a string into an integer number.
	int numberKey = atoi(key); 
	
	//Create a file pointer that points to the files we need to encrypt or decrypt.
	FILE *fp1; //File needed to encrypt/decrypt
	FILE *fp2; //Resulting file that is encrypted or decrypted
	
	//Create a local char array to hold the information in the first file as well as a another buffer to hold the encrypted/decrypted characters.
	char buffer[100];
	char encryptedBuffer[100];
				
	//If only one or two parameters are entered in, tell the user so and end the program.
	if (argc == 3)
	{
		printf("The name of the key, source file, or encrypted/decryped files are missing.\n");
		return 1;
	}	
	//Tries to open the first file for reading the information into the buffer array.
	fp1 = fopen(argv[2], "rb");

	//If the name is wrong or the file does not exist, throw and error and end the program.	
	if (fp1 == NULL)
	{
		printf("File open error.\n");
		return 1;
	}
	
	//Tries to open the second file for writing the infromation from the character array into a file.
	fp2 = fopen(argv[3], "wb");	
	
	//If the name is wrong or the file does not exist, throw an error and end the program.
	if (fp2 == NULL)
	{
		printf("File open error.\n");
		return 1;
	}
	
	//Set a while loop to read the file 100 bytes at a time (a char is 1 byte).
	while((ret = fread(buffer,sizeof(char),100,fp1)) > 0)
	{
		//Based on the number of sucessfull elements read, encrypt/decrypt the characters into a character array.
		for(i = 0; i < ret; i++)
		{
			encryptedBuffer[i] = buffer[i] ^ numberKey;
		}
		
		//Write the encrypted/decrypted characters to another file.
		fwrite(encryptedBuffer,sizeof(char),ret,fp2);
	}
	
	//Close the files once the encryption/decryption is complete.
	fclose(fp1);
	fclose(fp2);
	
	//End the program.
	return 1;
}
