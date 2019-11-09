#include "list.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
