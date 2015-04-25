#include <stdio.h>
#include <math.h>
#include <malloc.h>

int main (void)
{
	char * (Name[3]);
	Name[0] = (char *)malloc (5 * sizeof(char));
	Name[1] = (char *)malloc (5 * sizeof(char));
	Name[2] = (char *)malloc (5 * sizeof(char));
	printf ("str0 is \n");
	scanf ("%s", Name[0]);

	printf ("str1 is \n");
	scanf ("%s", Name[1]);

	printf ("str2 is \n");
	scanf ("%s", Name[2]);

	printf ("%s, %s, %s", Name[1], Name[2], Name[0]);
	getchar ();
	getchar ();
	return 0;
}