/******************************************************************/
/* Jordan Murtiff						  */
/* Lab #8						 	  */
/* Lab Section: Wednesday (60312)	                          */
/* Date: November 8, 2017				          */
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Define linked list that contains both the name and number of guests for each user as well as the address of the next
//node in the linked list. 
struct waitingList
{
	//1D array to hold the names entered in by the user.
	char nameOfPerson[30];
	
	//An integer variable to keep track of the number of guests in the user's party.	
	int numberOfGuests;

	//Declare a pointer that points to the next node in the linked list.
	struct waitingList *next;
};

//Declare all prototypes
void addPeople(char*, int);
int checkForDuplicates(char*); 
void removePeople();
void changeGuests();
void listGuests();
void readFromBinary(char*);
struct waitingList* reverseLinkedLists(struct waitingList*,struct waitingList*);
void quitProgram(char*,char*);

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
		
	//If only one parameter is entered in, tell the user so and end the program.
	if (argc == 2)
	{
		printf("The name of the text and/or binary files are missing.\n");
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


void addPeople(char name[], int number)
{		
	//Creates a variable that stores which linked list the new node should be added to.
	int index = 0;

	//Sees which linked list to add the new node to depending on the number of guests read from the file.
	if(number == 1 || number == 2)
	{
		index = 0;
	}
	else if(number == 3 || number == 4)
	{
		index = 1;
	}
	else if(number == 5 || number == 6)
	{
		index = 2;
	}
	else if(number >= 7)
	{
		index = 3;
	} 
	
	//Allocates memory for a new node.
	struct waitingList *newEntry;
	newEntry  = (struct waitingList*)malloc(sizeof(struct waitingList));
	
	//If there is not enough memory to allocate, tell the user so.	
	if (newEntry == NULL)
	{
		printf("Failed to allocate memory.\n");
		return;
	}

	//Copy the data from the file into the newly created node.
	strcpy(newEntry->nameOfPerson, name);
	newEntry->numberOfGuests = number;
	
	//Since the node is placed at the end of the linked list, it's next pointer should be NULL.
	newEntry->next = NULL;
		
	//If this is the first node in the linked list, set both head and tail to point to this node
	//(since it is both the first node and the last node of the list). 
	if(heads[index] == NULL && tails[index] == NULL)
	{  
		heads[index] = newEntry; 
		tails[index] = newEntry; 
	}

	//Otherwise if there is more than one node, you have to change the tail pointer to point to the "new"
	//node and change the previous node to point to this "new" node.
	else
	{
		tails[index]->next = newEntry; 
		tails[index] = newEntry; 		
	}	
}


int checkForDuplicates(char* name)
{
	//A variable is created to see if the user's name repeats in any of the nodes in the linked list.
	int partyFound = 0;
	
	//Checks to see if the name is already in one of the nodes in the linked list.
	//Goes through each array of linked lists individually, looking for the same name
	//as the user entered.
	for(int i=0; i<4; i++)
	{
		struct waitingList *ptr = heads[i];
		if(heads[i] == NULL)
		{
			continue;
		}
		else
		{
			while(ptr != NULL)
			{
				if(strcmp(ptr->nameOfPerson,name) == 0)
				{
					partyFound = 1;
					break;
				}
				else
				{
					ptr = ptr->next;
				}
			}
			if(partyFound == 1)
			{
				break;
			}
		}
	}

	//If a name was found that was the same as the user's input, then return 1 (true), otherwise return 0 (false). If no parties can be found, return 0 (false).
	if(partyFound == 1)
	{
		return 1;
	}
	else if (partyFound == 0)
	{
		return 0;
	}
	else
	{
		return 0;
	}
}


void removePeople()
{
	//A variable is created to see which linked list should be traversed first.
	int index = 0;	

	//A variable is created for the user to enter the number of guests at his/her table.
	int tableToRemove;

	//Prints out a command to enter the number of guests. 
	printf("Please type in the number of guests at your table:");

	//Takes in the input of the user.
	scanf("%d",&tableToRemove);

	//Based on what the user entered, find the most apprporiate linked list to start traversing.
	if(tableToRemove == 1 || tableToRemove == 2)
	{
		index = 0;
	}	
	else if(tableToRemove == 3 || tableToRemove == 4)
	{
		index = 1;
	}
	else if (tableToRemove == 5 || tableToRemove == 6)
	{
		index = 2;
	}
	else if (tableToRemove >= 7)
	{
		index = 3;
	}
	
	//Construct two pointers that point to the first node in the linked list as well as the one before it.
	//Use the "ptr" pointer to delete the node if it is found.
	struct waitingList *ptr;
	struct waitingList *qtr;
	
	//The variable "i" is created to see which linked list contains the node to be deleted.
	int i;
	for(i = index; i >= 0 ;i--)
	{	
		struct waitingList *p = heads[i];
		struct waitingList *q = heads[i];
		if(heads[i] == NULL)
		{
			continue;
		}
		else
		{
			while(p != NULL)
			{
				if(p->numberOfGuests <= tableToRemove)
				{
					ptr = p;
					qtr = q;
					break;
				}
				else
				{
					q = p;
					p = p->next;
				}
			}
			//If the node we want to delete is found, break out of the for loop.
			if(ptr == p)
			{
				break;
			}
		}
	}
		
	//If the list is empty, tell the user so and end the function.
	if (heads[i] == NULL)
	{
		printf("No parties with that number of guests exists.\n");
		return;
	}
	else
	{		
		//If that name does not exist in the list, tell the user so and
		//end the function.
		if (ptr == NULL)
		{
			printf("That party does not exist.\n");
			return;
		}
			
		//Prints out the data of the node being deleted.
		printf("Name of Guest is: %s\n", ptr->nameOfPerson);
		printf("Number of Guests: %i\n", ptr->numberOfGuests);
			
		//If the first node exists and is the one to be removed from the linked list.
		if (ptr == heads[i])
			{
				//If p is the only node in the linked list, you have to change both head and tail pointers
				//to point to NULL since after the deletion, no nodes will exist in the linked list.
				if (heads[i] == tails[i])
				{
					heads[i] = NULL;
					tails[i] = NULL;
				}
				//If p is not the only node in the linked list, then change the head pointer to
				//point to the node after the 1st node.
				else
				{
					heads[i] = heads[i]->next;
				}
			}
		//If the node to be deleted is at the end of the linked list, change the 2nd to last
		//node to have NULL as it's "next" value and make the tail pointer point to this node.
		else if (ptr == tails[i])
		{
			qtr->next = NULL;
			tails[i]= qtr;
		}	
	
		//If the node to be deleted is not the first or last node in the linked list, change the
		//node that "q" is pointing to instead point to the node following the one being deleted. 
		else
		{
			qtr->next = ptr->next;
		}
		
		//Frees the memory of the node to be removed so other nodes can allocate the same
		//memory.
		free(ptr);
	}
		
}

void changeGuests()
{
	//A variable is created to store the index of the linked list we want to remove.
	int index = 0;
	
	//A variable is created to see if the user's name repeats in any of the nodes in the linked list.
	int partyFound = 0;	

	//A variable is created for the user to enter his/her name.
	char name[30];
	
	//Prints out a command to enter the name.
	printf("Please type in your name:");

	scanf("%s", name);
	
	//Checks to see if the name the user ented is in one of the nodes in the linked list.
	//Goes through each array of linked lists individually, looking for the same name
	//as the user entered.		
	struct waitingList *ptr;
	struct waitingList *qtr;
	for(index=0; index<4; index++)
	{
		struct waitingList *p = heads[index];
		struct waitingList *q = heads[index];
		if(heads[index] == NULL)
		{
			continue;
		}
		else
		{
			while(p != NULL)
			{
				if(strcmp(p->nameOfPerson,name) == 0)
				{
					ptr = p;
					qtr = q;
					partyFound = 1;
					break;
				}
				else
				{
					q = p;
					p = p->next;
				}
			}
			if(partyFound == 1)
			{
				break;
			}
		}		
	}
		
	//If the name was not found that was the same as the user's input, then tell the user so.
	if(partyFound == 0)
	{
		printf("\nNo party with that name exists\n");
	}

	//Otherwise, if the name was found, ask the user for a new number of guests and 
	//possibly change the node to a different linked list.
	else
	{	
		//A variable is created to keep track of where the node is to be moved to,
		//if it is to be moved at all.
		int arrayValue = 0;
		
		//The user is asked to enter the number of guests at a table, a variable is created for this.
		int guestNumber;
		printf("Please type in a new number of guests:");
				
		//Takes in the user input.
		scanf("%i",&guestNumber);
		
		//Check to see which linked list the node is going to move to.
		if(guestNumber == 1 || guestNumber == 2)
		{
			arrayValue = 0;
		}
		else if(guestNumber == 3 || guestNumber == 4)
		{
			arrayValue = 1;
		}
		else if(guestNumber == 5 || guestNumber == 6)
		{
			arrayValue = 2;
		}
		else if (guestNumber >= 7)
		{
			arrayValue = 3;
		}
		
		//If the user entered a number of guests in the same range as the 
		//original location as the node, then the node does not move to
		//a different list. Tell the user so.
		if(index == arrayValue)
		{	
			printf("Your party does not change lists.\n");
			ptr->numberOfGuests = guestNumber;
		}
		else
		{	
			//Allocates memory for a new node.
			struct waitingList *newEntry;
			newEntry  = (struct waitingList*)malloc(sizeof(struct waitingList));
	
			//If there is not enough memory to allocate, tell the user so.	
			if (newEntry == NULL)
			{
				printf("Failed to allocate memory\n");
				return;
			}

			//Copy the number of guests entered in by the user into the newly created node.
			//keep the name the same as the node to be removed.
			strcpy(newEntry->nameOfPerson, ptr->nameOfPerson);
			newEntry->numberOfGuests = guestNumber;
	
			//Since the node is placed at the end of the linked list, it's next pointer should be null.
			newEntry->next = NULL;
		
			//If this is the first node in the linked list, set both head and tail to point to this node
			//(since it is both the first node and the last node of the list). 
			if(heads[arrayValue] == NULL && tails[arrayValue] == NULL)
			{  
				heads[arrayValue] = newEntry; 
				tails[arrayValue] = newEntry; 
			}

			//Otherwise if there is more than one node, you have to change the tail pointer to point to the "new"
			//node and change the previous node to point to this "new" node.
			else
			{
				tails[arrayValue]->next = newEntry; 
				tails[arrayValue] = newEntry; 		
			}
			
			//Since the new node has been created, now we have to delete the old node.
			//Follow the same pattern of deletion as the removePeople function. Index
			//gives you the specific linked list you want to delete the node from.
				
			//If the first node exists and is the one to be removed from the linked list.
			if (ptr == heads[index])
				{
					//If ptr is the only node in the linked list, you have to change both head and tail pointers
					//to point to NULL since after the deletion, no nodes will exist in the linked list.
					if (heads[index] == tails[index])
					{
						heads[index] = NULL;
						tails[index] = NULL;
					}
					//If ptr is not the only node in the linked list, then change the head pointer to
					//point to the node after the 1st node.
					else
					{
						heads[index] = heads[index]->next;
					}
				}
			//If the node to be deleted is at the end of the linked list, change the 2nd to last
			//node to have NULL as it's "next" value and make the tail pointer point to this node.
			else if (ptr == tails[index])
			{
				qtr->next = NULL;
				tails[index]= qtr;
			}	
		
			//If the node to be deleted is not the first or last node in the linked list, change the
			//node that "qtr" is pointing to instead point to the node following the one being deleted. 
			else
			{
				qtr->next = ptr->next;
			}
			
			//Frees the memory of the node to be removed so other nodes can allocate the same
			//memory.
			free(ptr);			
		}
	}	
}

void readFromBinary(char* nameOfBinaryFile)
{
	//After writing all the party information into the file, deallocate all the nodes in each linked list.
	//Look through all the linked lists and delete each node found.
	for(int i = 0; i <4; i++)
	{
		struct waitingList *ptr = heads[i];
		struct waitingList *qtr = NULL;
		//If the linked list is empty, move to the next linked list.	
		if(ptr == NULL)
		{
			continue;
		}
		else
		{
			//If there is more than one node, then set a temporary pointer to point to the next node after the node to be deleted. Once it's at the end of the linked list, it moves on to the next list.
			while (ptr !=  NULL)
			{
				qtr = ptr;
				free(qtr);
				ptr = ptr->next;
			}	
		}
	heads[i] = NULL;
	tails[i] = NULL;
	}	
	//Show a sucessfull deallocation of nodes.
	printf("All nodes have been freed.\n");


	//After deleting all the nodes from the array of linked lists, read the nodes from the binary file into the array of linked lists.

	//Create a file pointer and open the binary file for reading.
	FILE *fp;
	fp = fopen(nameOfBinaryFile, "rb");

	if (fp == NULL)
	{
		printf("File read error.");
		return;
	}
	
	//Allocate memory for a new node to be read by the binary file (so the binary file knows what to read).	
	struct waitingList *newNode;
	newNode = (struct waitingList*)malloc(sizeof(struct waitingList));

	//Read from the binary file and put the data into the array of linked lists.
	while(fread(newNode, sizeof(struct waitingList), 1, fp) > 0)
	{
		char *name = newNode->nameOfPerson;
		int number = newNode->numberOfGuests;
		addPeople(name, number);
		struct waitingList *newNode;
		newNode = (struct waitingList*)malloc(sizeof(struct waitingList));
	}
	fclose(fp);
}

struct waitingList* reverseLinkedLists(struct waitingList *head, struct waitingList *previous)
{ 
	//Declare a temporary node that is used in the recursive call.	
	struct waitingList *temp;
	
	//If there is nothing in the linked list, return the head pointer to NULL.
	if(head == NULL)
	{
		return NULL;
	}

	//If there is only one node in the linked list, return head as that node and keep head->next to NULL.
	if(head->next == NULL)
	{
		head->next = previous;
		return head;
	}

	//Otherwise, if there is more than one node, move to the end of the list, reversing the "next" pointers until you reach the end of the list. Once you are at the end of the linked list, change the head pointer.
	else
	{
		temp = reverseLinkedLists(head->next, head);
		head->next = previous;
		return temp;
	}
	
}


void quitProgram(char* nameOfTextFile, char* nameOfBinaryFile)
{
	//Creates two file pointers that will point to the text and binary files we are trying to write to.
	FILE *fp1;
	FILE *fp2;	

	//Opens the file in writing mode so we can write in the names and guest numbers of all the parties.
	fp1 = fopen(nameOfTextFile, "w");

	//Creates a variable to hold the header string for the text file.
	char header [] = "Name\t\tGroup Size\n--------------------------\n";

	//Write the header to the text file.
	fprintf(fp1,"%s", header);

	//A for loop traverses each linked list and writes the party information into the text file.
	int i;	
	for(i=0; i<4; i++)
	{
		struct waitingList *ptr = heads[i];
		if(heads[i] == NULL)
		{
			continue;
		}
		else
		{
			//Looks through each node in the linked list and writes the name and number of guests for each person in the list up until the last node.
			while(ptr != NULL)
			{
				fprintf(fp1,"%s\t\t%d\n", ptr->nameOfPerson,ptr->numberOfGuests);
				ptr = ptr->next;
			}		
		}
	}

	//Close the text file.
	fclose(fp1);
	
	
	//Open the binary file for writing.
	fp2 = fopen(nameOfBinaryFile, "wb");

	//A for loop traverses each linked list and writes the party information into the binary file.
	int j;	
	for(j=0; j<4; j++)
	{
		struct waitingList *ptr = heads[j];
		if(heads[j] == NULL)
		{
			continue;
		}
		else
		{
			//Write the node from the array of linked list into the binqry file.
			while(ptr != NULL)
			{
				fwrite(ptr, sizeof(struct waitingList),1,fp2);
				ptr = ptr->next;
			}	
		}
	}
	
	//Close the binary file.
	fclose(fp2);

	//After writing all the party information into the file, deallocate all the nodes in each linked list.
	//Look through all the linked lists and delete each node found.
	for(int i = 0; i <4; i++)
	{
		struct waitingList *ptr = heads[i];
		struct waitingList *qtr = NULL;
		//If the linked list is empty, move to the next linked list.	
		if(ptr == NULL)
		{
			continue;
		}
		else
		{
			//If there is more than one node, then set a temporary pointer to point to the next node after the node to be deleted. Once it's at the end of the linked list, it moves on to the next list.
			while (ptr !=  NULL)
			{
				qtr = ptr;
				free(qtr);
				ptr = ptr->next;
			}	
		}
	}	
	//Show a sucessfull deallocation of nodes.
	printf("All nodes have been freed.\n");
}

void listGuests()
{
	int i = 0;
	//Use a for loop to print out each individual node in the different linked lists.  
	for(i=0; i<4; i++)
	{
		struct waitingList *ptr = heads[i];
		if(heads[i] == NULL)
		{
			continue;
		}
		else
		{
			//Looks through each node in the linked list and prints out the name and number of guests for each person in the list up until the last node.
			printf("\nGroup Number is: %i", i+1); 
			while(ptr != NULL)
			{		
				printf("\nName of Guest: %s\n",ptr->nameOfPerson);		
				printf("Number of Guests: %i\n",ptr->numberOfGuests);
				ptr = ptr->next;
			}		
		}
	}
}
