#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataStruct.h"
#define BUS "BUS DATA��FOLLOWS"
#define BRANCH "BRANCH DATA FOLLOWS"

int ImportData (char *);
int main (void)
{
	char DataName[20];
	printf ("Please enter the Power Flow Data name:");
	scanf (" %s", DataName);
	ImportData (DataName);
	Branch_Type Branch[Nbranch];
	Bus_Type Bus[Nbus];
	getchar ();
	getchar ();
	return 0;
}		    Data (char *DataName)
{
	FILE * fpin, * fptmp;
	int ch;
	fpin = fopen (DataName,"rb");
	fptmp = tmpfile ();		//������ʱ�ļ����ڴ���trim��������ļ�
	char Line[130];
	/*trim blank*/
	while ( (ch = getc (fpin)) != EOF )
	{
		if ( ch != ' ' )	//�����Ϊ�ո��ַ��ͻ����ַ�
			putc (ch, fptmp);
		else
		{
			//ֻ����һ���ո񣬺�����ַ�
			while ( (ch = getc (fpin)) == ' ' );
			putc (' ', fptmp);
			putc (ch, fptmp);
		}
	}
	/*Import Data which are in a Line*/
	while ( fgets (Line, 129, fptmp ) != EOF )
	{

	}
				//fscanf (fptmp,"%s %s %s", flag_tmp[0], flag_tmp[1], flag_tmp[2]);
		//printf ("%s,%s,%s\n", flag_tmp[0], flag_tmp[1], flag_tmp[2]);
	}
	printf ("%d is '\'n, %d is '\'r", j, i);
	return 0;
}