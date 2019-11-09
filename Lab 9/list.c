#include "list.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
