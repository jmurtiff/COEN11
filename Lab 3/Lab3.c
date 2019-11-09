/******************************************************************/
/* Jordan Murtiff						  */
/* Lab #3						 	  */
/* Lab Section: Wednesday (60312)	                          */
/*							          */
/* This program is a waiting list for a restaurant. It takes a    */
/* number (from 1-4) that carries out a specific command. If the  */
/* user presses 1, then the program asks for the user's name and  */
/* the number of people in the user's party. This information is  */
/* recorded in an array of structures where one structure contains*/
/* a user's name and the number of guests associated with the     */
/* user's party. If the user presses 2, then the program asks for */
/* the number of guests in the user's party and then removes the  */
/* array element containing the oldest structure with that        */
/* specific number of people in the user's party. If the user     */
/* presses 3, then the program prints out the array of structures */
/* containing both the names and guest numbers of people on the   */
/* waiting list. If the user presses 4, the program quits.        */

#include <stdio.h>
#include <string.h>

//Declare all prototypes
void addPeople(); 
void removePeople();
void listGuests();

//Define structure that contains both the name and the number of guests for each user.
struct waitingList
{
	//1D array to hold the names entered in by the user.
	char nameOfPerson[30];
	
	//An integer variable to keep track of the number of guests in the user's party.
	int numberOfGuests;
};

//Define array of structures that holds both the name and number of guests for each user.
struct waitingList totalWaitingList[30];

//Counter to keep track of which spot in the list is empty (next in line).
int counter = 0;


int main()
{	
		//Prints out options for the user to pick from.
		printf("What do you wish to do?\n");
		printf("Enter 1 to reserve your table with name and number of guests\n");
		printf("Enter 2 to remove the oldest entry with a specific number of guests\n");
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
	//A variable is created to see if the user's name repeats anywhere in the name member of the array of structures.
	int partyFound = 0;
	
	//A variable is created for the user to enter his/her name.
	char name[30];
	
	//Prints out a command to enter the name.
	printf("Please type in your name:");

	//Takes in the input of the user.
	scanf("%s",name);
	
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.   
	struct waitingList *ptr;
	ptr = totalWaitingList;
	
	//Checks to see if the name member is already in the array of structures.
	for (int r = 0; r <=counter; r++,ptr++)
	{
		if(strcmp(ptr->nameOfPerson,name)==0)
		{
			partyFound = 1;
			break;
		}
	}	
	
	//If a name was found that was the same as the user's input, then tell the user so.
	if(partyFound == 1)
	{
		printf("That name is on the list already.\n\n");
	}

	//If the name is unique to the array of structures, add it to the name member of a structure.
	else
	{
		//Checks to see if the array of structures is full by checking where the counter is compared to the length of the array of structures.
		if (counter < 30)
		{
			//Copies the user input into the name member in the array of structures.
			strcpy(totalWaitingList[counter].nameOfPerson,name);

			//The user is asked to enter the number of guests at a table, a variable is created for this.
			int guestNumber;
			printf("Please type in the number of guests:");
				
			//Takes in the user input.
			scanf("%i",&guestNumber);
			
			//Puts the user's input into a guest number member in the array of structures.	
			totalWaitingList[counter].numberOfGuests = guestNumber;
				
			//Moves to the next structure in the array of structures.
			counter++;
		}
		
		//If the array of structures (waiting list) is full, tell the user so.
		else
		{
			printf("Cannot insert name and party, waiting list is full.\n");
		}
	}
}


void removePeople()
{
	//A variable is created to see whether or not the user's number is in a member in the array of structures.
	int numberOfGuestsFound;
	
	//A variable is created for the user to enter the number of guests at his/her table.
	int tableToRemove;

	//A variable is created to show which structure has to be removed.
	int indexOfTable;

	//Prints out a command to enter the number of guests. 
	printf("Please type in the number of guests at your table:");

	//Takes in the input of the user.
	scanf("%d",&tableToRemove);
	
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.   
	struct waitingList *ptr;
	ptr = totalWaitingList;

	//Searches through the guest number members in the array of structures to find the oldest entry matching the user's input.
	for (int r = 0 ; r <counter; r++,ptr++)
	{
		if (ptr->numberOfGuests == tableToRemove)	
		{
			numberOfGuestsFound = 1;
			indexOfTable = r;
			break;
		}
	}

	//Removes the specified table and moves all other names and guest numbers on the waitlist up.
	if (numberOfGuestsFound == 1)
	{
		//Prints out the name and the number of guests at the table to be removed.
		printf("Name of Guest: %s\n", totalWaitingList[indexOfTable].nameOfPerson);
		printf("Number of Guests: %i\n\n",totalWaitingList[indexOfTable].numberOfGuests);

		//Moves all other entries up 1 for both names and guest numbers.
		for (int i =  indexOfTable; i < counter; i++)
		{
			strcpy(totalWaitingList[i].nameOfPerson,totalWaitingList[i+1].nameOfPerson);
			totalWaitingList[i].numberOfGuests = totalWaitingList[i+1].numberOfGuests;
		}
		counter -= 1;
	}
	
	//If the user enters a number that does not match any number in the guest number member in the array of structures, tell the user so.
	else
	{
		printf("That party does not exist.\n");
	}
}

void listGuests()
{
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.   
	struct waitingList *ptr;
	ptr = totalWaitingList;

	//Looks through the array of strucutres and prints the name and number members up until it reaches the counter.
	for (int r = 0; r <counter; r++, ptr++)
		{ 
			printf("\nName of Guest: %s\n",ptr->nameOfPerson);		
			printf("Number of Guests: %i\n\n",ptr->numberOfGuests);
		}
}
