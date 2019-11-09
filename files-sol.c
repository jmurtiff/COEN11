/*	Question 1
 *	Write a function to return the number of even integers in a text file.
 *	The function receives the file pointer (FILE *) as an argument.
 */
int
even (FILE *fp)
{
	int	i;
	int	number;
	int	counter = 0;
	
	if (fp == NULL)
	{
		printf ("no file\n");
		return;
	}

	while (fscanf (fp, "%d", &number) == 1)
	{
		if (number % 2 == 0)
			counter++;
	}

	return (counter);
}


/*	Question 2
 *	Write a function to return the number of even integers in a binary file.
 *	The function receives the file pointer (FILE *) as an argument.
 */
int
even (FILE *fp)
{
	int	i, ret;
	int	counter = 0
	int	buffer[SIZE];
	
	if (fp == NULL)
		return -1;

	while ((ret = fread (buffer, sizeof(int), SIZE, fp)) > 0)
	{
		for (i = 0; i < ret; i++)
			if (buffer[i] % 2 == 0)
				counter++;
	}

	return (counter);
}

/*	Question 3
 *	Write a function to initialize array x of size SIZE with integers read from a text file.
 *	The function receives the name of the file as an argument.
 */
void
init (char *name)
{
	FILE	*fp;
	int	i;
	
	fp = fopen (name, "r");
	if (fp == NULL)
	{
		printf ("no file\n");
		return;
	}

	for (i = 0; i < SIZE; i++)
	{
		if (fscanf (fp, "%d", &x[i]) < 1)
		{
			printf ("got %d numbers\n", i);
			return;
		}
	}

	fclose (fp);
	return;
}


/*	Question 4
 *	Write a function to initialize array x of size SIZE with integers read from a binary file.
 *	The function receives the name of the file as an argument.
 */
void
init (char *name)
{
	FILE	*fp;
	int	i;
	
	fp = fopen (name, "br");
	if (fp == NULL)
	{
		printf ("no file\n");
		return;
	}

	if (fread (x, sizeof (int), SIZE, fp) < 1)
		printf ("error reading\n");

	fclose (fp);
	return;
}


/*	Question 5
 *	Write a void function to copy a file into another file.
 *	The function receives the two FILE pointers (src and dest) as arguments.
 *	Use fread, fwrite, and an array to make the process more efficient!
 */
void
copy (FILE *fp1, FILE *fp2)
{
	int	ret;
	char	buffer[SIZE];
	
	while ((ret = fread (buffer, sizeof(char), SIZE, fp1)) > 0)
		fwrite (buffer, sizeof(char), ret, fp2);

	return;
}


/*	Question 6
 *	Write a function to create a linked list with nodes obtained from a binary file.
 *	The function receives the file pointer (FILE *) as an argument.
 */
void
link (FILE *fp)
{
	NODE	*temp;
	
	if (fp == NULL)
	{	
		printf ("no file\n");
		return;
	}
	
	temp = (NODE *)malloc (sizeof (NODE));
	
	if (temp == NULL)
		return;

	while (fread (temp, sizeof(NODE), 1, fp) > 0)
	{
		insert (temp);
		temp = (NODE *)malloc (sizeof (NODE));
	}
	
	return;
}

/*
 *	Question 7
 *	Write an int function to return the average of the int numbers read from a binary file.
 *	The function receives the name of the file.
 *	Use fread, fwrite, and an array to make the process more efficient!
 */
int
average (char *name)
{
	FILE	*fp;
	int	i, ret;
	int	sum = 0;
	int	counter = 0
	int	buffer[SIZE];
	
	fp = fopen (name, "rb");
	if (fp == NULL)
		return -1;

	while ((ret = fread (buffer, sizeof(int), SIZE, fp) > 0)
	{
		for (i = 0; i < ret; i++)
			sum += buffer[i]);
		counter += ret;
	}

	fclose (fp);

	return (sum / counter);
}

/*	Question 8
 *	Write a void function to compare two files.
 *	Your function should receive the file pointers (src and dest) and
 *	printf either “Files are equal.\n” or “Files are not equal.\n”.
 *	Use fread, fwrite, and an array to make the process more efficient! 
 */
void
compare (FILE *fp1, FILE *fp2)
{
	int	i;
	int	ret1;
	int	ret2;
	char	buffer1[SIZE];
	char	buffer2[SIZE];
	
	while (1)
	{
		ret1 = fread (buffer1, sizeof(char), SIZE, fp1);
		ret2 = fread (buffer2, sizeof(char), SIZE, fp2);

		//	not same size
		if (ret1 != ret2)
		{
			printf ("Files are not equal\n");
			return;
		}

		//	done
		if (ret1 < 1)
		{
			printf ("Files are equal\n");
			return;
		}

		for (i = 0; i < ret1; i++)
		{
			if (buffer1[i] != buffer2[i])	
			{
				printf ("Files are not equal\n");
				return;
			}
		}
	}

	return;
}
