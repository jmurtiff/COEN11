/*****************************************************************/
/* Lab 2 - Jordan Murtiff - September 2017                       */
/*					                         */
/* This program is a waiting list for a restaurant. It takes a   */
/* number (from 1-4) that carries out a specific command. If the */
/* user presses 1, then the program asks for the user's name and */
/* the number of people in the user's party. This information is */
/* recorded in two arrays (one for name and one for number of    */
/* guests). If the user presses 2, then the program asks for the */
/* number of guests in the user's party and then removes both the*/
/* name and the number of guests from the party with a specific  */
/* number of people in it. If the user presses 3, then both the  */
/* 2D array of guest names and well as the number of guests tied */
/* to each name will be printed out from oldest to newest (from  */ 
/* top to bottom). If the user presses 4, the program quits.     */

#include <stdio.h>
#include <string.h>

//Declare all prototypes
void addPeople(); 
void removePeople();
void listGuests();

//Counter to keep track of which spot in the list is empty (next in line).
int counter;

//2D array to hold the names entered in by the user.
char nameOfPerson[30][30];

//1D array to keep track of the number of guests in the user's party.
int numberOfGuests[30];

int main()
{	
		//Prints out options for the user to pick from.
		printf("What do you wish to do?\n");
		printf("Enter 1 to reserve your table with name and number of guests\n");
		printf("Enter 2 to remove the oldest entry with a specific number of guests\n");
		printf("Enter 3 to show the lists of all names and numbers of guests\n");
		printf("Enter 4 to quit the program\n");
		while(1) //infinite loop that allows user to continually accept commands 
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
	//A variable is created to see if the user's name repeats anywhere in the 2D array of names.
	int partyFound = 0;
	
	//A variable is created for the user to enter his/her name.
	char name[30];
	
	//Prints out a command to enter the name.
	printf("Please type in your name:");

	//Takes in the input of the user.
	scanf("%s",name);
	
	for (int r = 0; r <= counter; r++)
	{
		//Checks to see if the 2D array has a name that is the same.
		if (strcmp(nameOfPerson[r],name)==0) 
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

	//If the name is unique to the list, add it to the list.
	else
	{
		//Checks to see if the 2D array of names is full by checking where counter is compared to the length of the 2D Array.
		if (counter < 30)
		{
			//Copies the user input into the 2D array of names.
			strcpy(nameOfPerson[counter],name);

			//The user is asked to enter the number of guests at a table, a variable is created for this.
			int guestNumber;
			printf("Please type in the number of guests:");
				
			//Takes in the user input.
			scanf("%i",&guestNumber);
			
			//Puts the user's input into an array for the number of guests at a table.	
			numberOfGuests[counter] = guestNumber;
				
			//Moves to the next row in the 2D array of names.
			counter++;
		}
		
		//If the 2D array of names is full, tell the user so.
		else
		{
			printf("Cannot insert name and party, list is full.\n");
		}
	}
}


void removePeople()
{
	//A variable is created to see whether or not the user's number is in the 1D array of guest numbers.
	int numberOfGuestsFound;
	
	//A variable is created for the user to enter the number of guests at his/her table.
	int tableToRemove;

	//A variable is created to show which spot in the list has to be removed.
	int indexOfTable;

	//Prints out a command to enter the number of guests. 
	printf("Please type in the number of guests at your table:");

	//Takes in the input of the user.
	scanf("%d",&tableToRemove);

	//Searches through the array numberOfGuests to find the oldest entry matching the user's input.
	for (int r =0 ; r <counter; r++)
	{
		if (numberOfGuests[r] == tableToRemove)	
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
		printf("Name of Guest: %s\n", nameOfPerson[indexOfTable]);
		printf("Number of Guests: %i\n\n", numberOfGuests[indexOfTable]);

		//Moves all other entries up 1 for both names and guest numbers.
		for (int i =  indexOfTable; i < counter; i++)
		{
			strcpy(nameOfPerson[i], nameOfPerson[i+1]);
			numberOfGuests[i] = numberOfGuests[i+1];
		}
		counter -= 1;
	}
	
	//If the user enters a number that does not match any number in numberOfGuests, tell the user so.
	else
	{
		printf("That party does not exist.\n");
	}
}

void listGuests()
{
	//Looks through the 2D Array of names and the 1D array of guests and prints all of them out until it reaches the counter.
	for (int r = 0; r <counter; r++)
		{ 
			printf("\nName of Guest: %s\n", nameOfPerson[r]);		
			printf("Number of Guests: %i\n\n", numberOfGuests[r]);
		}
}




