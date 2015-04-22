#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStruct.h"
int ImportData (char *);
int main (void)
{
	char DataName[20];
	printf ("Please enter the Power Flow Data name:");
	scanf (" %s", DataName);
	ImportData (DataName);
	Branch_Type Branch[Nbranch];
	getchar ();
	getchar ();
	return 0;
}
int ImportData (DataName)
{
	FILE * fpin;
	int ch;
	fpin = fopen (DataName,"r");
	while ( (ch = getc(fpin)) != EOF )
	{
		if ( ch != ' ' )	//输出不为0字符
			putc (ch, stdout);
		else
		{
			//只保留一个空格，后输出字符
			while ( (ch = getc (fpin)) == ' ' );	
			putc (' ', stdout);
			putc (ch, stdout);
		}
	}
}