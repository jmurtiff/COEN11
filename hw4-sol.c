/*
 *************************************************
 *
 *	COEN 11 -- Homework 4
 *	Doubly-Linked Lists -- insert and delete specific nodes
 *	Fall 2017
 *
 *************************************************
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#define NODE	struct node


struct node
{
	int	number;
	NODE	*prev;
	NODE	*next;
};


NODE	*head = NULL;
NODE	*tail = NULL;
int	counter = 0;


void	insert (NODE *, NODE *);
void	delete (NODE *);
void	show (void);



/*
 *************************************************
 *
 *	insert
 *
 *************************************************
 */
void
insert (NODE *temp, NODE *position)
{
	
	if (temp == NULL)
	{
		printf ("insert error\n");
		return;
	}


	if (head == NULL)
	{
		head = tail = temp;
		temp->prev = temp->next = NULL;
	}
	else if (position == head)
	{
		temp->next = position;
		temp->prev = NULL;
		position->prev = temp;
		head = temp;
	}
	else if (position == NULL)
	{
		temp->prev = tail;
		temp->next = NULL;
		tail->next = temp;
		tail = temp;
	}
	else 	//include position == tail
	{
		temp->next = position;
		temp->prev = position->prev;
		position->prev->next = temp;
		position->prev = temp;
	}

	return;
}


/*
 *************************************************
 *
 *	delete
 *
 *************************************************
 */
void
delete (NODE *p)
{
	if (head == NULL)
	{
		printf ("the list is empty\n");
		return;
	}

	if (p == NULL)
	{
		printf ("delete error\n");
		return;
	}

	if (head == p  &&  tail == p)
		head = tail = NULL;
	else if (head == p)
	{
		head = head->next;
		head->prev = NULL;
	}
	else if (tail == p)
	{
		tail = tail->prev;
		tail->next = NULL;
	}
	else
	{
		p->next->prev = p->prev;
		p->prev->next = p->next;
	}

	free (p);
	return;
}


/*
 *************************************************
 *
 *	print
 *
 *************************************************
 */
void
show ( )
{
	NODE	*p;

	if (head == NULL)
	{
		printf ("the list is empty\n");
		return;
	}

	printf ("**********\n");
	p = head;
	while (p !=  NULL)
	{
		printf ("%d\n", p->number);
		p = p->next;
	}
	printf ("**********\n");

	return;
}

		
	
