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
	//向临时文件写入IEEE标准格式的潮流数据
	while ( (ch = getc (fpin)) != EOF )
	{
		putc (ch, fptmp);
	}

	if ( fclose (fpin) != 0 )	//关闭输入文件及判断其是否正常关闭
	{
		printf ("Error in closing file %s\n", DataName);
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	
	initialize_RawData (RawData, fptmp);	//初始化潮流数据结构体并赋值

	if ( fclose (fptmp) != 0 )	//关闭临时文件及判断其是否正常关闭
	{
		printf ("Error in closing temporary file\n");
		printf ("Press Enter to Quit!!");
		getchar ();
		getchar ();
		exit (2);
	}
	return;
}