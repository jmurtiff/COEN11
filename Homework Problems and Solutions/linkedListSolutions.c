/*
 *************************************************
 *
 *   Unordered Linked Lists - Fall 2017 COEN 11
 *
 *************************************************
 */

#include	<stdio.h>
#include	<stdlib.h>


//#define	NODE	struct node
typedef struct node
{
	int	number;
	struct node	*next;
}NODE;

NODE	*head = NULL;


void	insert (int);
NODE	*search (int);
void	delete (int);
void	list ( );

/*
 *************************************************
 *
 *	main
 *
 *************************************************
 */
int
main ( )
{
	char	cmd[10];
	int	number;
	NODE	*p;

	while (1)
	{
		scanf ("%s", cmd);
		switch (cmd[0])
		{
			case 'i':
				scanf ("%d", &number);
				insert (number);
				break;

			case 's':
				scanf ("%d", &number);
				if (search (number) != NULL)
					printf ("Found it!\n");
				else
					printf ("Not there!\n");
				break;

			case 'd':
				scanf ("%d", &number);
				delete (number);
				break;

			case 'l':
				list ( );
				break;

			case 'q':
				printf ("Quiting...\n");
				return;
				break;

			default:
				printf ("Not an accepted command...\n");
				break;
		}
	}

	return 0;
}


/*
 *************************************************
 *
 *	insert
 *
 *************************************************
 */
void
insert (int number)
{
	NODE	*temp;

	if ((temp = (NODE *) malloc (sizeof (NODE))) == NULL)
	{
		printf ("Malloc error...\n");
		exit (1);
	}

	temp->number = number;
	temp->next = head;
	head = temp;
}


/*
 *************************************************
 *
 *	search
 *
 *************************************************
 */
NODE	*
search (int number)
{
	NODE	*p;

	p = head;
	while (p !=  NULL)
	{
		if (p->number == number)
			return (p);
		p = p->next;
	}

	return (NULL);
}


/*
 *************************************************
 *
 *	delete
 *
 *************************************************
 */
void
delete (int number)
{
	NODE	*p;
	NODE	*q;

	if (head == NULL)
	{
		printf ("The list is empty.\n");
		return;
	}

	p = q = head;
	while (p !=  NULL)
	{
		if (p->number == number)
			break;
	
		q = p;
		p = p->next;
	}

	if (p == NULL)
	{
		printf ("Number %d is not in the list.\n", number);
		return;
	}

	if (p == head)
		head = p->next;
	else
		q->next = p->next;

	free (p);
	return;
}


/*
 *************************************************
 *
 *	list
 *
 *************************************************
 */
void
list ( )
{
	NODE	*p;

	if (head == NULL)
	{
		printf ("The list is empty.\n");
		return;
	}

	printf ("The numbers are:\n");
	p = head;
	while (p !=  NULL)
	{
		printf ("%d\n", p->number);
		p = p->next;
	}

}

		
	
