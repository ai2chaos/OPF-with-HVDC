#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main (void)
{
	FILE * fpin;
	int ch;
	fpin = fopen ("014ieee.DAT", "r");
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
	getchar ();
	return 0;
}