/******************************************************************/
/* Jordan Murtiff						  */
/* Lab #10						 	  */
/* Lab Section: Wednesday (60312)	                          */
/* Date: November 29, 2017				          */
/*							  	  */
/* This program is a waiting list for a restaurant. It takes a    */
/* number (from 1-7) that carries out a specific command. First,  */
/* the program tries to open and read a text file containing the  */
/* information about each party and tries to put this information */
/* into an array of linked lists. If the text and/or binary file  */ 
/* does not exist or the name of the text or binary file cannot be*/ 
/* found, a file is created instead with a header included. If the*/
/* user presses 1, then the program asks for the user's name and  */
/*  number of guests and puts this information into an array of   */ 
/* linked lists, where one node contains the user's name, number  */ 
/* of guests associated with the user's party, and a pointer to   */ 
/* the next node in the list. Depending on the number of guests   */ 
/* the user enters, a node will be created in a specific linked   */
/* list depending on the range. Linked lists will contain parties */
/* from 1-2, 3-4, 5-6, and parties greater than 7. Each new entry */
/*  will go into one of the ranges listed above. If the user      */ 
/* presses 2, then the program asks for the number of guests in   */
/* the user's party and removes specific node containing less than*/
/* or equal to the number of guests entered. The program searches */ 
/* through the array of linked lists to find the oldest entry     */
/* matching this criteria and deletes the node. If the user       */
/* presses 3, then the program prints out every node in the linked*/
/* list in the array of linked lists. If the user presses 4, then */ 
/* the program asks for the program asks for the user's name and  */ 
/* asks for a new number of guests. If the user enters a new      */
/* number of guests that is lower or higher than the original     */
/*reservation range, than it changes that node to be at the end of*/
/* the respective linked list. If the user presses 5, then the    */ 
/* program erases all the nodes from the array of linked lists and*/
/* reads information from the binary file into the array of linked*/
/* list. The nodes in the array of linked lists are printed out.  */ 
/*If the user presses 6, then the program reverses the order of   */ 
/* each linked list in the array of linked lists. If the user     */ 
/* presses 5, then the program writes all the data from the array */
/* of linked lists into a text and binary file (header included   */
/* with the text file) and then quits the program.                */		

#include "file.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//Declare an array of head pointers (that points to the first node) and a tail pointers (that points to the last node)
//as NULL before any nodes are created in the array of linked lists. 
struct waitingList *heads[4] = {NULL,NULL, NULL, NULL};
struct waitingList *tails[4] = {NULL,NULL, NULL, NULL};


int main(int argc, char*argv[])
{
	//Create a file pointer that points to the text file we are reading and writing in.
	FILE *fp1; //Text file
	FILE *fp2; //Binary file
	
	//Create two local variables that stores the user's name and number of guests when reading from the file.
	char name[30];
	int number;

	//Create a variable that stores the name of the file we are reading and writing from. Use this in the "quitProgram" function to pass the name to the file pointer.
	char* nameOfTextFile = argv[1];
	char* nameOfBinaryFile = argv[2];
		
	//If only one or two parametes are entered in, tell the user so and end the program.
	if (argc == 2)
	{
		printf("The name of the text, binary, and/or autosave text files missing.\n");
		return 1;
	}	
	else
	{
		//Creates a header string that is printed to the top of the file before any data is read.	
		char header [] = "Name\t\tGroup Size\n--------------------------\n";

		//Tries to open the text file for reading the names and group sizes of every party.
		fp1 = fopen(argv[1], "r");
		
		//If the name is wrong or the file does not exist, create a new file and print the header inside. At the end. make sure to set the file to reading mode.	
		if (fp1 == NULL)
		{
			printf("Text file unable to be found, creating new file now.\n");
			fp1 = fopen(argv[1], "w");
			fprintf(fp1,"%s\n", header);
			fclose(fp1);
			fp1 = fopen(argv[1], "r");
		}
		//Start reading the file after the header.	
		fseek(fp1, strlen(header), SEEK_SET);

		//Continually searches through the file and adds each party to the respective linked list.
		while(fscanf(fp1,"%s%d",name,&number) == 2)
		{
			addPeople(name,number);
		}
		
		//Close the file after you are done reading it.
		fclose(fp1);

		//Tries to open the binary file to see if it exists.
		fp2 = fopen(argv[2], "rb");
	
		//If the name is wrong or the file does not exist, create a new binary file. At the end, close the file.	
		if (fp2 == NULL)
		{
			printf("Binary file unable to be found, creating new file now.\n");
			fp2 = fopen(argv[2], "wb");
			fclose(fp2);
		}
		else
		{
			fclose(fp2);
		}	
	}
	
	//Prints out options for the user to pick from.
	printf("What do you wish to do?\n");
	printf("Enter 1 to reserve your table with name and number of guests\n");
	printf("Enter 2 to remove the oldest entry with a size less than or equal to a specified number of guests\n");
	printf("Enter 3 to show the lists of all names and numbers of guests\n");
	printf("Enter 4 to change party size\n");
	printf("Enter 5 to read the parties from a binary file into the array of linked lists\n");
	printf("Enter 6 to reverse the order of the array of linked lists\n");
	printf("Enter 7 to write data to a text and binary file, deallocate memory, and quit the program\n");
		
	//Infinite loop that allows user to continually accept commands.
	while(1)
	{
		//Asks the user to make a choice from 1-7 and stores it in a variable.
		int choice;
		printf("\nEnter your choice here:");
		scanf("%i",&choice);

		//Switch structure allows the user to do one part of the program after entering a number from 1-7.
		switch(choice)
			{
				case 1:	
					//Prints out a command to enter the name.
					printf("Please type in your name:");

					//Takes in the input of the user.
					scanf("%s",name);
					 
					//If a name was found that was the same as the user's input, then tell the user so.
					if(checkForDuplicates(name) == 1)
					{
						printf("That name is on the list already.\n\n");
						break;
					}
					
					//If the name is unique to the array of linked lists, add it to a node in the list.
					else
					{	
						//The user is asked to enter the number of guests at a table, a variable is created for this.
						int guestNumber;
						printf("Please type in the number of guests:");
	
						//Takes in the user input.
						scanf("%i",&guestNumber);
	
						//Adds the name and number of guests to a node in the array of linked lists.
						addPeople(name, guestNumber);
						break;
					}
				case 2:
					removePeople();
					break;
				case 3:
					listGuests();
					break;
				case 4:
					changeGuests();
					break;
				case 5:
					readFromBinary(nameOfBinaryFile);
					listGuests();
					break;
				case 6:
					for(int i = 0; i <4; i++)
					{
						if(tails[i] != NULL)
						{
							tails[i] = heads[i];
						}
						heads[i] = reverseLinkedLists(heads[i],NULL);
					}
					break;
				case 7:
					quitProgram(nameOfTextFile,nameOfBinaryFile);
					return 0;
				default:
					printf("Error! That is not an accepted command, please type in a number from 1-6\n");
					break;
			}
	}
}
