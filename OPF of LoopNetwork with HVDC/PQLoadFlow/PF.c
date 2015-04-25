#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PowerFlow.h"
#define BUS "BUS DATA FOLLOWS"
#define BRANCH "BRANCH DATA FOLLOWS"

int ImportData (void);
int main (void)
{
	char DataName[20];
	//printf ("Please enter the Power Flow Data name:");
	//scanf (" %s", DataName);
	RawData_Type * RawData;
	RawData = (RawData_Type *)malloc (sizeof(RawData_Type));
	ImportData (DataName);
	Branch_Type Branch[Nbranch];
	Bus_Type Bus[Nbus];
	getchar ();
	getchar ();
	return 0;
}		  

int ImportData (void)
{
	FILE * fpin, * fptmp;
	int ch;
	if ( (fpin = fopen (IEEE14, "rb")) == NULL )
	{
		printf ("Can't open this file, Please check your Data Name!\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (1);
	}
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
	if ( fclose (fpin) != 0 )	//�ر������ļ����ж����Ƿ������ر�
	{
		printf ("Error in closing file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	/*Import Data which are in a Line*/
	rewind (fptmp);		//�ص��ļ�ͷ������������ļ�ָ�볬���ļ���Χ,�γ�����
	while ( fgets (Line, 129, fptmp ) != NULL )
	{
		//��ȡBUS����
		if ( strncmp (Line, BUS, 16) ==0 )
		{
			fgets (Line, 129, fptmp);
			while ( strncmp (Line, "-999", 4) != 0 )
			{
				printf ("%s", Line);
				fgets (Line, 129, fptmp);
			}
		}
		//��ȡBRANCH����
		if ( strncmp (Line, BRANCH, 19) == 0 )
		{
			fgets (Line, 129, fptmp);
			while ( strncmp (Line, "-999", 4) != 0 )
			{
				printf ("%s", Line);
				fgets (Line, 129, fptmp);
			}
		}

		//printf ("%s", Line);
		//fscanf (fptmp,"%s %s %s", flag_tmp[0], flag_tmp[1], flag_tmp[2]);
		//printf ("%s,%s,%s\n", flag_tmp[0], flag_tmp[1], flag_tmp[2]);
	}
	return 0;
}