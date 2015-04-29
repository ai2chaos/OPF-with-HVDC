#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PowerFlow.h"

void ImportData (RawData_Type * RawData)
{
	FILE * fpin, * fptmp;
	int ch;
	if ( (fpin = fopen (IEEE14, "r")) == NULL )
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
	/*
	rewind (fptmp);		//回到文件头部，不添加则文件指针超出文件范围,形成乱码
	while ( (ch = getc (fptmp)) != EOF )
	{
	putc (ch, stdout);
	}
	rewind (fptmp);		//回到文件头部，不添加则文件指针超出文件范围,形成乱码
	while ( fgets (Line, 303, fptmp ) != NULL )
	{
	//读取bus数据
	if ( strncmp (Line, BUS, 16) == 0 )
	{
	for ( i = 0, fgets (Line, 303, fptmp); i < Nbus && (strncmp (Line, "-999", 4) !=0);	i++, fgets (Line, 303, fptmp))
	{
	printf ("%d,%s", i+1, Line);
	sscanf (Line, "%d %12[0-9A-Z-' ']s  %d", RawData->BusData[i].BusNum, RawData->BusData[i].Name,
	RawData->BusData[i].LFarea);
	sscanf (Line, "%4d %12[0-9-A-Z ]s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d",
	RawData->BusData[i].BusNum, RawData->BusData[i].Name, RawData->BusData[i].LFarea,
	RawData->BusData[i].LossZone, RawData->BusData[i].Type, RawData->BusData[i].Vol,
	RawData->BusData[i].Deg, RawData->BusData[i].PL, RawData->BusData[i].QL,
	RawData->BusData[i].PG, RawData->BusData[i].QG, RawData->BusData[i].BaseVol,
	RawData->BusData[i].DesiredVol, RawData->BusData[i].MaxVol,
	RawData->BusData[i].MinVol, RawData->BusData[i].ShuntG, RawData->BusData[i].ShuntB,
	RawData->BusData[i].RemoteCtrlBus);
	}
	}
	//读取BRANCH数据
	if ( strncmp (Line, BRANCH, 19) == 0 )
	{
	for ( j = 0, fgets (Line, 303, fptmp); j < Nbranch && (strncmp (Line, "-999", 4) != 0); j++, fgets (Line, 303, fptmp))
	{
	printf ("%d,%s\n", j + 1, Line);
	}
	}
	}
	*/
	return;
}