#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void)
{
	FILE * fp;
	int ch;
	//ºÏ≤È√¸¡Ó––
	fp = fopen ("testcase.txt", "r");
	ch = getc (fp);
	while (ch != EOF)
	{
		if ()
		{
		}
		putchar (ch);
		ch = getc (fp);
	}
	getchar ();
	return 0;
}