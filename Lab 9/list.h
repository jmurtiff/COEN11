//Jordan Murtiff, Lab9, Wednesday 11/15/17
//Header file for list prototypes and global variables.

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

//Declare an array of head pointers (that points to the first node) and a tail pointers (that points to the last node)
//as NULL before any nodes are created in the array of linked lists. 
extern struct waitingList *heads[4];
extern struct waitingList *tails[4];
