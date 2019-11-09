//Jordan Murtiff
//Date: December 8, 2017

//This program creates a linked lists of tasks that can be manipulated to add, delete,
//find maximum prority number, and save to a text file.

//Libraries used in the program.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Head and Tail pointers for the linked lists of tasks.
//Set to NULL due to empty list.
struct list *head = NULL;
struct list *tail = NULL;

//Structure used for every task. Contains a description, prioirty number, and a pointer to the next node
//in the linked list.
struct list
{
	//200 character description.
	char description[200];

	//Priority number used for other functions.
	int num;
	
	//Structure pointer that points to the next node in the linked list of tasks.
	struct list *next;
};

//All protoypes for all functions.
void addTask(void);
void deleteTask(void);
void showTask(void);
void getMax(void);
int recursionTask(struct list*, int);
void saveToTextFile(void);

int main()
{
	//Intialize a variable for the user to pick a number from 1-6.
	int choice;

	//Infinite while loop with switch statement depending on what the user
	//picks.
	while(1)
	{
		printf("\nEnter 1 to add a new task\n");
		printf("Enter 2 to delete a task with priority number\n");
		printf("Enter 3 to show all tasks\n");
		printf("Enter 4 to find the maximum priority number\n");
		printf("Enter 5 to save tasks to text file\n");
		printf("Enter 6 to quit program\n");
		printf("Enter your choice here:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				addTask();
				break;
			case 2:
				deleteTask();
				break;
			case 3:
				showTask();
				break;
			case 4:
				getMax();
				break;
			case 5:
				saveToTextFile();
				break;
			case 6:
				return 0;
			default:
				printf("\nPlease enter a number from 1-6\n");
				
		}
	}
}


void addTask(void)
{
	//Allocate memory for a new node in the linked list.
	struct list *newNode;
	newNode = (struct list*) malloc(sizeof(struct list));

	//Create a pointer that will be used to traverse the linked list.
	struct list *p;

	//Take in the description entered in by the user.
	char summary[200];	
	printf("\nEnter Description here:");
	scanf("%s", summary);
	strcpy(newNode->description,summary);

	//Take in the priority number entered in by the user.
	int number;
	printf("\nEnter Prority number here:");
	scanf("%d",&number);
	newNode->num = number;

	//Set "p" pointer to point to the first node in the linked list.
	p = head;

	//Traverse through the linked list, ensuring that the user's priority number is unique.
	//If it is not, then end the function.
	while(p != NULL)
	{
		if(p->num == newNode->num)
		{
			printf("\nPriority number used, try another.\n\n");
			free(newNode);
			return;
		}
		else
		{
			p = p->next;
		}
	}
	//If the priority number is not in one of the nodes in the linked list
	//add the new node to the end of the linked list.

	//If the node is the first in the list, set head and tail pointers to NULL
	//and the newNode's next pointer to NULL.
	if(head == NULL)
	{
		newNode->next = NULL;
		tail = head = newNode;
	}
	
	//If there is only one node in the linked list, set head's net pointer to point to
	//the new node and tail to equal the new node (since you add at the end of the linked list).
	//Then, set newNode's next pointer to NULL since it is at the end of the list. 
	else if (head == tail)
	{
		head->next = newNode;
		tail = newNode;
		newNode->next = NULL;
	}

	//If there is more than one node in the linked list, then set the last node (which 
	//tail is pointing to) to point to this newNode and make tail equal the newNode (since
	//it is at the end of the linked list) and set newNode's next pointer to NULL (since 
	//it is at the end of the list. 
	else
	{
		tail->next = newNode;
		newNode->next = NULL;
		tail = newNode;
	}
}


void deleteTask(void)
{
	//Declare two list pointers that wil help in deleting a node.
	struct list *p;
	struct list *q;

	//Intialize a variable to hold the user's priority number.
	int priority;

	//If the list is empty, there is nothing to delete.	
	if(head == NULL)
	{
		printf("\nEmpty list, no tasks can be deleted.\n");
		return;
	}

	//Tell the user to enter a priorty number and take in that number.	
	printf("\nEnter Priority number:");
	scanf("%i", &priority);

	//Traverse through the linked list looking for the node with the user's priority number.
	p = q = head;
	while (p != NULL)
	{
		if(p->num == priority)
		{
			break;
		}
		else
		{
			q = p;
			p = p->next;
		}
	}
	
	//If a node with the user's priority number could not be found, end the function.
	if(p==NULL)
	{
		printf("\nTask with that priority number does not exist.\n");
		return;
	}
	
	//Print out the node to be deleted.
	printf("\nDescription is: %s\n", p->description);
	printf("Priority number is: %i\n", p->num);

	//If the node to be deleted is the only node in the linked list, set head and 
	//tail pointers to NULL and free the node. Otherwise, set head to point to the node
	//after itself and free the previous head node.   
	if(p == head)
	{
		if(head == tail)
		{
			head = tail = NULL;
			free(p);
		}
		else
		{
			head = head -> next;
			free(p);
		}
	}
	
	//If the node to be deleted is at the end of the list, then set tail to equal the 2nd to 
	//last node and it's next pointer to be NULL. Then, free the node.
	else if (p == tail)
	{
		tail = q;
		q->next = NULL;
		free(p);
	}

	//If the node to be deleted is in the middle of the list (neither head or tail), then
	//set q (the node before the one that is deleted) to point to the node after the node being
	//deleted (in this case being q). Then, free the node.
	else
	{
		q->next = p->next;
		free(p);
	}
	
	//Print a statement if a node has been sucessfully deleted.
	printf("Task deleted.\n");
}
		
	
void showTask(void)
{
	//Create a list pointer that will traverse the linked list.
	struct list *p;

	//If the list is empty, print a statement saying so and then end the function.
	if(head == NULL)
	{
		printf("\nList is empty. There is nothing to show.\n");
		return;
	}

	//Traverse through the linked list, printing out all the nodes.
	p = head;
	while(p!=NULL)
	{
		printf("\nDescription is: %s\n", p->description);
		printf("Priority number is: %i\n", p->num);
		p = p->next;
	}
}


void getMax(void)
{
	//Create a list pointer that will help traverse the linked list recursively.
	struct list *p;

	//Create a varaible to store the maximum value we are looking for.
	int maximum;

	//If the list is empty, return that there is no maximum.	
	if(head == NULL)
	{
		printf("List is empty,no maximum can be found.\n");
		return;
	}

	//Take the maximum from the first task in the linked list.
	//Note: This may not be the maximum we end up with, but we can
	//use it to compare the other priority numbers between the different tasks.
	//If there is a maximum that is not the first node, the recursive function
	//will replace the maxium with that value.
	p = head;
	maximum = p->num;

	//Find the maximum priority number using recursion.
	int recursive = recursiveTask(p,maximum);

	//Print out the maximum priority number.
	printf("\nMaximum priority number is: %i\n", recursive);
}

int recursiveTask(struct list *node, int maximum)
{
	//If you have reached the end of the list, return the maximum priority number.  	
	if(node  == NULL)
	{
		return maximum;	
	}
	else
	{
		//If the priority number of the task is greater than the previous maximum prioirty number, set it to that value (i.e. if the prioirty number in the node is 7 while the parameter's maximum is 5, change the parameter maximum to 7). 
		if(node->num > maximum)
		{
			maximum = node->num;
			return recursiveTask(node->next,maximum);
		}
		else
		{
			//If the priority number is the same or smaller than the current maximum, then move on to the
			//next node.
			return recursiveTask(node->next,maximum);
		}
	}	
}

void saveToTextFile()
{
	//Create a file pointer that we will use to write the linked list to a text file.  
	FILE *fp1;

	//Create a list pointer used to traverse the linked list.
	struct list *p;
	p = head;

	//Open the text file in writing mode.
	fp1 = fopen("tasks.txt", "w");
	
	//Traverse the linked list, printing the information in the nodes
	//to the text file, one line is one tasks (description and prority number).
	while(p != NULL)
	{
		fprintf(fp1,"%s\t%i\n",p->description,p->num);
		p = p->next;
	}
	
	//Close the file once all nodes have been written to the text file.
	fclose(fp1);

	//Print out that the linked list has been sucessfully written to the text file. 
	printf("\nSucessfully saved to text file!\n");
}


