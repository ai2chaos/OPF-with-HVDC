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
		if ( ch != ' ' )	//�����Ϊ0�ַ�
			putc (ch, stdout);
		else
		{
			//ֻ����һ���ո񣬺�����ַ�
			while ( (ch = getc (fpin)) == ' ' );	
			putc (' ', stdout);
			putc (ch, stdout);
		}
	}
}