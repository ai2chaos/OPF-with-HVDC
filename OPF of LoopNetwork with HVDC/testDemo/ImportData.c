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
	getchar ();
	return 0;
}