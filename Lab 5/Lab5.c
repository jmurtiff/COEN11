/******************************************************************/
/* Jordan Murtiff						  */
/* Lab #5						 	  */
/* Lab Section: Wednesday (60312)	                          */
/* Date: October 18, 2017				          */
/*							  	  */
/* This program is a waiting list for a restaurant. It takes a    */
/* number (from 1-4) that carries out a specific command. If the  */
/* user presses 1, then the program asks for the user's name and  */
/* the number of people in the user's party. This information is  */
/* recorded in a linked list where one node in the list contains  */
/* a user's name, number of guests associated with the user's     */
/* party, and a pointer to the next node in the list. If the user */
/* presses 2, then the program asks for the number of guests in   */
/* the user's party and removes the specifc node containing less  */
/* than or equal to the number of people in the user's party. If  */
/* the user presses 3, then the program prints out the linked list*/
/* containing both the names and guest numbers of people on the   */
/* waiting list. If the user presses 4, the program quits.        */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Declare all prototypes
void addPeople(); 
void removePeople();
void listGuests();

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

//Declare a head pointer (that points to the first node) and a tail pointer (that points to the last node)
//as NULL before any nodes are created in the linked list. 
struct waitingList *head = NULL;
struct waitingList *tail = NULL;

int main()
{	
		//Prints out options for the user to pick from.
		printf("What do you wish to do?\n");
		printf("Enter 1 to reserve your table with name and number of guests\n");
		printf("Enter 2 to remove the oldest entry with a size less than or equal to a specified number of guests\n");
		printf("Enter 3 to show the lists of all names and numbers of guests\n");
		printf("Enter 4 to quit the program\n");
		
		//Infinite loop that allows user to continually accept commands.
		while(1)
		{
			//Asks the user to make a choice from 1-4 and stores it in a variable.
			int choice;
			printf("\nEnter your choice here:");
			scanf("%i",&choice);

			//Switch structure allows the user to do one part of the program after entering a number from 1-4.
			switch(choice)
				{
					case 1:
						addPeople();
						break;
					case 2:
						removePeople();
						break;
					case 3:
						listGuests();
						break;
					case 4:
						return 0;
					default:
						printf("Error! That is not an accepted command, please type in a number from 1-4\n");
						break;
				}
		}
}


void addPeople()
{
	//A variable is created to see if the user's name repeats in any of the nodes in the linked list.
	int partyFound = 0;
	
	//A variable is created for the user to enter his/her name.
	char name[30];
	
	//Prints out a command to enter the name.
	printf("Please type in your name:");

	//Takes in the input of the user.
	scanf("%s",name);
	
	//Construct a pointer that points to the first node in the linked list.
	//Use this to traverse through the linked list.
	struct waitingList *ptr = head;
	
	//Checks to see if the name is already in one of the nodes in the linked list.
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
	
	//If a name was found that was the same as the user's input, then tell the user so.
	if(partyFound == 1)
	{
		printf("That name is on the list already.\n\n");
	}

	//If the name is unique to the linked list, add it to a node in the list.
	else
	{		
		//The user is asked to enter the number of guests at a table, a variable is created for this.
		int guestNumber;
		printf("Please type in the number of guests:");
				
		//Takes in the user input.
		scanf("%i",&guestNumber);		
		
		//A new node is allocated in memory.
		struct waitingList* newEntry;
		newEntry = (struct waitingList*)malloc(sizeof(struct waitingList));
	
		//If there is not enough memory to allocate, tell the user so.	
		if (newEntry == NULL)
		{
			printf("Failed to Allocate Memory\n");
			return;
		}

		//Copy the data entered in by the user into the newly created node.
		strcpy(newEntry->nameOfPerson, name);
		newEntry->numberOfGuests = guestNumber;
	
		//Since the node is placed at the end of the linked list, it's next pointer should be null.
		newEntry->next = NULL;
		
		//If this is the first node in the linked list, set both head and tail to point to this node
		//(since it is both the first node and the last node of the list). 
		if(head == NULL && tail == NULL)
		{
			head = newEntry; 
			tail = newEntry; 
		}

		//Otherwise if there is more than one node, you have to change the tail pointer to point to the "new"
		//node and change the previous node to point to this "new" node.
		else
		{
			tail->next = newEntry; 
			tail = newEntry; 		
		}
	}
}
	

void removePeople()
{	
	//A variable is created for the user to enter the number of guests at his/her table.
	int tableToRemove;

	//Prints out a command to enter the number of guests. 
	printf("Please type in the number of guests at your table:");

	//Takes in the input of the user.
	scanf("%d",&tableToRemove);
	
	//Construct two pointers that point to the first node in the linked list as well as the one before it.
	//Use the "p" pointer to traverse through the linked list.
	struct waitingList *p = head;
	struct waitingList *q = head;
	
	//If the list is empty, tell the user so and end the function.	
	if (head == NULL)
	{
		printf("The waiting list is empty, no entries can be found.\n");
		return;
	}

	//Checks to see if the name member is already in the linked list. The pointer "q" is always one node
	//behind the "p" pointer and can be used when a node is to be removed that is not either at the 
	//end or the beginning of the linked list. 
	while(p != NULL)
	{
		if(p->numberOfGuests <= tableToRemove)
		{
			break;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}

	//If that name does not exist in the list, tell the user so and
	//end the function.
	if (p == NULL)
	{
		printf("That party does not exist.\n");
		return;
	}
		
	//Prints out the data of the node being deleted.
	printf("Name of Guest is: %s\n", p->nameOfPerson);
	printf("Number of Guests: %i\n", p->numberOfGuests);

	//If the first node exists and is the one to be removed from the linked list.
	if (p == head)
	{
		//If p is the only node in the linked list, you have to change both head and tail pointers
		//to point to NULL since after the deletion, no nodes will exist in the linked list.
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}

		//If p is not the only node in the linked list, then change the head pointer to
		//point to the node after the 1st node.
		else
		{
			head = head->next;
		}
	}
	
	//If the node to be deleted is at the end of the linked list, change the 2nd to last
	//node to have NULL as it's "next" value and make the tail pointer point to this node.
	else if (p == tail)
	{
		q->next = NULL;
		tail = q;
	}	

	//If the node to be deleted is not the first or last node in the linked list, change the
	//node that "q" is pointing to instead point to the node following the one being deleted. 
	else
	{
		q->next = p->next;
	}
	
	//Frees the memory of the node to be removed so other nodes can allocate the same
	//memory.
	free(p);
}

void listGuests()
{	   
	//Construct a pointer that points to the first node in the linked list.
	//Use this to traverse through the linked list.
	struct waitingList *ptr;
	ptr = head;

	//Looks through each node in the linked list and prints out the name and number of guests for each person in the list up until the last node.
	while(ptr != NULL)
	{ 	printf("\nName of Guest: %s\n",ptr->nameOfPerson);		
		printf("Number of Guests: %i\n",ptr->numberOfGuests);
		ptr = ptr->next;
	}
}
