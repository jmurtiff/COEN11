/******************************************************************/
/* Jordan Murtiff						  */
/* Lab #4						 	  */
/* Lab Section: Wednesday (60312)		 		  */
/* Date: October 10, 2017		                          */
/*							          */
/* This program is a people list. It takes a number (from 0-3)    */
/* that carries out a specific command. If the user presses 0,    */
/* then the program asks for the user's name and age. With the age*/
/* the user typed in, the program asks for the user's status. This*/
/* status depends on if the user is either less than or equal to  */
/* 21 years of age, between 21 and 65 years of age (non-inclusive)*/
/* ,or if the user is greater than or equal to 65 years of age.   */
/* All of this information is put into an array of structures with*/
/* structure holding the name (int), name (arrray of char), and   */
/* a union holding the correct status based on the user's age.    */
/* If the user presses 1, then the program asks for a name that is*/
/* then searched through in the array of structures and deleted if*/
/* the specific name matches the name element of the structure.   */
/* If the user presses 2, then the program prints out the array of*/
/* structures containing the name, age, and status of each person */
/* on the list. If the user presses 3, the program quits.         */

#include <stdio.h>
#include <string.h>

//Declare all prototypes
void addPeople(); 
void removePeople();
void listPeople();

//Define the union that can hold either the name of school, salary per month, or age of retirement for a person.
union status
{
	char nameOfSchool[30];
	float salaryPerMonth;
	int yearsOfRetirement;
};

//Define structure that contains both the name and the number of guests for each user.
struct peopleList
{
	//1D array to hold the names entered in by the user.
	char nameOfPerson[30];
	
	//An integer variable to hold the age entered in by the user.
	int ageOfPerson;

	//A union variable that holds the status of a person.
	union status statusOfPerson; 
};

//Define array of structures that holds both the name, age, and status for each user.
struct peopleList totalPeopleList[30];

//Counter to keep track of which spot in the list is empty (next in line).
int counter = 0;


int main()
{	
		//Prints out options for the user to pick from.
		printf("What do you wish to do?\n");
		printf("Enter 0 to add your name, age, and status to the list\n");
		printf("Enter 1 to remove the oldest entry with a specific name\n");
		printf("Enter 2 to show the lists of all names, ages, and statuses\n");
		printf("Enter 3 to quit the program\n");
		
		//Infinite loop that allows user to continually accept commands.
		while(1) 
		{
			//Asks the user to make a choice from 0-3 and stores it in a variable.
			int choice;
			printf("\nEnter your choice here:");
			scanf("%i",&choice);

			//Switch structure allows the user to do one part of the program after entering a number from 0-3.
			switch(choice)
				{
					case 0:
						addPeople();
						break;
					case 1:
						removePeople();
						break;
					case 2:
						listPeople();
						break;
					case 3:
						return 0;
					default:
						printf("Error! That is not an accepted command, please type in a number from 0-3.\n");
						break;
				}
		}
}


void addPeople()
{
	//A variable is created to see whether the name the user entered is already in the array of structures.
	int nameFound = 0;

	//A variable is created for the user to enter his/her name.
	char name[30];
	
	//Prints out a command to enter the name.
	printf("Please type in your name:");
	
	//Takes in the input of the user.
	scanf("%s",name);
	
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.    
	struct peopleList *ptr;
	ptr = totalPeopleList;
	
	//Checks to see if the name member is already in the array of structures.
	for (int r = 0; r <counter; r++,ptr++)
	{
		if(strcmp(ptr->nameOfPerson,name)==0)
		{
			nameFound = 1;
			break;
		}
	}	
	
	//If a name was found that was the same as the user's input, then tell the user so.
	if(nameFound == 1)
	{
		printf("That name is on the list already.\n\n");
	}

	//Otherwise if the name is not a repeat, check if the array of structures is full by checking where the counter is compared to the length of the array of structures.
	//If both conditions are false, add the name, age, and status to the array of structures.
	else if (nameFound == 0 && counter < 30)
	{
		
		//Copies the user input into the name member in the array of structures.
		strcpy(totalPeopleList[counter].nameOfPerson,name);
		
		//A variable is created for the user to enter his/her age.
		int age;
		
		//Prints out a command to enter the age.
		printf("Please type in your age:");
		
		//Takes in the input of the user.
		scanf("%i",&age);
		
		//Puts the user's age into the age member in the array of structures.
		totalPeopleList[counter].ageOfPerson = age;
		
		//Age is classifed into certain status. Depending on the status of the person
		//the specific variable is put into the union member in the array of structures.
		if (age <= 21)
		{
			char schoolName[30];
			printf("Please type in the name of your school:");
			scanf("%s", schoolName);
			strcpy(totalPeopleList[counter].statusOfPerson.nameOfSchool,schoolName);
		}
		else if (age > 21 && age < 65)
		{
			float salary;
			printf("Please type in your monthly salary:");
			scanf("%f",&salary);
			totalPeopleList[counter].statusOfPerson.salaryPerMonth = salary;
		}
		else if (age >= 65)
		{
			int retirement;
			printf("Please type in the number of retirement years:");
			scanf("%i",&retirement);
			totalPeopleList[counter].statusOfPerson.yearsOfRetirement = retirement;
		}
					
		//Moves to the next structure in the array of structures.
		counter++;
	}

	//If the array of structures (people list) is full, tell the user so.
	else
	{
		printf("Cannot insert name and party, waiting list is full.\n");
	}
}

void removePeople()
{
	//A variable is created to take in the user's name.
	char name[30];

	//A variable is created to see whether or not the user's name is in the array of structures.
	int nameFound = 0;

	//A variable is created to show which structure has to be removed.
	int indexOfName;

	//Prints out a command to enter the entry to be removed. 
	printf("Please type in the name of the entry to be removed:");

	//Takes in the input of the user.
	scanf("%s",name);
	
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.    
	struct peopleList *ptr;
	ptr = totalPeopleList;

	//Searches through the name members in the array of structures to find the name matching the user's input.
	for (int r = 0; r <counter; r++,ptr++)
	{
		if(strcmp(ptr->nameOfPerson,name)==0)
		{
			nameFound = 1;
			indexOfName = r;
			break;
		}
	}	
	//Overrides the specified structure and replaces it with the last valid element in the array of structures.
	//Only overrides the specific status based on the last valid structure's age (union variable can only take one variable). 
	if (nameFound == 1)
	{
		strcpy(totalPeopleList[indexOfName].nameOfPerson,totalPeopleList[counter-1].nameOfPerson);
		totalPeopleList[indexOfName].ageOfPerson = totalPeopleList[counter-1].ageOfPerson;
		int age = totalPeopleList[counter-1].ageOfPerson;
		if (age	<= 21)
		{	
			strcpy(totalPeopleList[indexOfName].statusOfPerson.nameOfSchool,totalPeopleList[counter-1].statusOfPerson.nameOfSchool);
		}

		else if (age > 21 && age < 65)
		{
			totalPeopleList[indexOfName].statusOfPerson.salaryPerMonth = totalPeopleList[counter-1].statusOfPerson.salaryPerMonth;
		}

		else if (age >= 65)
		{
			totalPeopleList[indexOfName].statusOfPerson.yearsOfRetirement = totalPeopleList[counter-1].statusOfPerson.yearsOfRetirement;
		}
		counter -=1;
	}
	
	//If the user enters a name that does not match any name members in the array of structures, tell the user so.
	else
	{
		printf("That name and entry do not exist.\n");
	}
}

void listPeople()
{
	//Construct a pointer that points to the first element in the array of structures. 
	//Use this to traverse through the array of structures.    
	struct peopleList *ptr;
	ptr = totalPeopleList;

	//Looks through the array of structures and prints the name, age, and status members of the array of structures up until the counter.
	for (int r = 0; r < counter; r++, ptr++)
		{ 
			printf("\nName of Person: %s\n",ptr->nameOfPerson);		
			printf("Age of Person: %i\n",ptr->ageOfPerson);
			if (ptr->ageOfPerson <= 21)
			{
				printf("Name of school is:%s\n", ptr->statusOfPerson.nameOfSchool);
			}
			else if (ptr->ageOfPerson > 21 && ptr->ageOfPerson < 65)
			{
				printf("Salary per month is:%f dollars\n", ptr->statusOfPerson.salaryPerMonth);
			}
			else if (ptr->ageOfPerson >= 65)
			{
				printf("Years of retirement is:%i years\n", ptr->statusOfPerson.yearsOfRetirement);
			}
		}
}
