/*
 *	Question 3
 */
int sum (int array[NROWS][NCOLS])
{
	int	i, j;
	int	sum = 0;

	for (i = 0; i < NROWS; i++)
	{
		for (j = 0; j < NCOLS; j++)
			sum += array[i][j];
	}

	return sum;

}


/*
 *	Question 4
 */
void init ( )
{
	int	i, j;

	for (i = 0; i < M; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (i == j  ||  i + j == M - 1)
				array[i][j] = 1;
			else
				array[i][j] = 0;
		}
	}

	return;
}


/*
 *	Question 5
 */
int count_strings (char *str)
{
	int	flag = 0;
	int	counter = 0;

	while (*str != '\0')
	{
		if (*str != ' '  &&  *str != '\t'  &&  *str != '\n')
		{
			if (flag == 0)
			{
				flag = 1;
				counter++;
				printf("here char is %c and count is %d\n", *str, counter);
			}

		}
		else
			flag = 0;
		str++;
	}

	return counter;	
}


/*
 *	Question 6
 */
int largest_size (char strings[NROWS][NCOLS])
{
	int	largest = 0;
	int	size = 0;
	int	i;
	char	*p;

	for (i = 0; i < NROWS; i++)
	{
		p = strings[i];
		size = 0;
		while (*p != '\0')
		{
			size++;
			p++;
		}
		if (size > largest)
			largest = size;
	}

	return largest;
}
