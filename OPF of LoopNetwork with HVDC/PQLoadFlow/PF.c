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
	fptmp = tmpfile ();		//创建临时文件用于储存trim后的数据文件
	char Line[130];
	/*trim blank*/
	while ( (ch = getc (fpin)) != EOF )
	{
		if ( ch != ' ' )	//输出不为空格字符和换行字符
			putc (ch, fptmp);
		else
		{
			//只保留一个空格，后输出字符
			while ( (ch = getc (fpin)) == ' ' );
			putc (' ', fptmp);
			putc (ch, fptmp);
		}
	}
	if ( fclose (fpin) != 0 )	//关闭输入文件及判断其是否正常关闭
	{
		printf ("Error in closing file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	/*Import Data which are in a Line*/
	rewind (fptmp);		//回到文件头部，不添加则文件指针超出文件范围,形成乱码
	while ( fgets (Line, 129, fptmp ) != NULL )
	{
		//读取BUS数据
		if ( strncmp (Line, BUS, 16) ==0 )
		{
			fgets (Line, 129, fptmp);
			while ( strncmp (Line, "-999", 4) != 0 )
			{
				printf ("%s", Line);
				fgets (Line, 129, fptmp);
			}
		}
		//读取BRANCH数据
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