#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PowerFlow.h"

void ImportData (RawData_Type * RawData)
{
	FILE * fpin, * fptmp;
	int ch;
	if ( (fpin = fopen (DataName, "r")) == NULL )
	{
		printf ("Can't open this file, Please check your Data Name!\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (1);
	}
	fptmp = tmpfile ();		//创建临时文件用于储存trim后的数据文件
	//char Line[303];
	//向缓冲文件读入数据
	/*
	//trim blank
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
	*/
	while ( (ch = getc (fpin)) != EOF )
	{
		putc (ch, fptmp);
	}

	if ( fclose (fpin) != 0 )	//关闭输入文件及判断其是否正常关闭
	{
		printf ("Error in closing file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	initialize_RawData (RawData, fptmp);
	return;
}