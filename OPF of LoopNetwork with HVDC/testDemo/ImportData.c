#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void)
{
	FILE * fp;
	int ch;
	//���������
	fp = fopen ("testcase.txt", "r");
	ch = getc (fp);
	while (ch != EOF)
	{
		putchar (ch);
		ch = getc (fp);
	}
	return 0;
}