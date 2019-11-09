/**************************************************************/
/* Lab 1 - Jordan Murtiff - September 2017                    */
/* This program generates a random divisor (from 0 to 12) and */
/* and a quotient (from 1 to 12) and finds the dividend. Once */
/* Once the dividend is calculated, both the dividend and the */
/* divisor is printed out and the user has to guess the       */
/* quotient. After 10 trials, a score is calculated out of 10.*/ 


#include <stdio.h>
#include <stdlib.h>

//Global variables
int divisor, quotient, dividend, isCorrect, userScore, userGuess;

int main()
{
	//The user starts with no correct answers, therefore the score is 0.
	userScore = 0;
	
	srand ((int) time (NULL));

	//The for loop runs the Division test 10 times.
	for (int i=0;i<10;i++)
	{
		//Generates a random divisor (from 0 to 12).
		divisor = rand()%12+1;
		
		//Generates a random quotient (from 1 to 12).
		quotient = rand()%13;

		//Multiplies the divisor by the quotient to find the dividend.
		dividend = divisor*quotient;
	
		//Prints out the current dividend value.
		printf("The dividend is %d\n", dividend);

		//Prints out the current divisor.
		printf("The divisor is %d\n", divisor);

		/*Asks the user to guess the quotient and increases the
		 score by 1 if the user correctly guesses the quotient*/
		isCorrect = division(divisor,quotient);
		if (isCorrect == 1)
			{
				userScore++;
			}
	}
	//Prints out the user's end score
	printf("Your total score is: %d/10\n", userScore);

	//Exit program
	return 0;
}

int division(divisor,quotient)
{
	//Asks the user to guess the quotient.
	printf("What is the quotient?\n");
	
	//Takes in the user's guess
	scanf("%d", &userGuess);
	
	//If the user's guess is the same as the quotient, then the user got the division problem correct.
	if (quotient == userGuess)
		{
			//Tells the user the quotient is correct and prints the correct quotient.
			printf("Correct, the quotient is %d\n\n", quotient);
			return 1;
		}
		else
		{
			//Tells the user the quotient is incorrect and prints the correct quotient.
			printf("Incorrect, the quotient is %d\n\n", quotient);
			return 0;
		}
}
