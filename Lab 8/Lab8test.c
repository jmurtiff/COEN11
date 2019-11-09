#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main(int argc, char*argv[])
{
	FILE *fp;
	fp = fopen(argv[1],"wb");
	int x = 10;

	char test[] = "This is a string";

	fwrite(test, sizeof(test-1), 1, fp);
	return;


}
