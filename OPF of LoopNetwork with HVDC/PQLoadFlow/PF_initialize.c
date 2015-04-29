#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PowerFlow.h"
#define BUS "BUS DATA FOLLOWS"
#define BRANCH "BRANCH DATA FOLLOWS"

void initialize_RawData (RawData_Type * RawData, FILE * fptmp)
{
	char Line[303];
	int i, j;
	rewind (fptmp);		//回到文件头部，不添加则文件指针超出文件范围,形成乱码
	while ( fgets (Line, 303, fptmp) != NULL )
	{
		//读取bus数据
		if ( strncmp (Line, BUS, 16) == 0 )
		{
			for ( i = 0, fgets (Line, 303, fptmp); i < Nbus && (strncmp (Line, "-999", 4) != 0); i++, fgets (Line, 303, fptmp) )
			{
				initialize_BusData (&(RawData->BusData[i]), Line);
			}
		}
		//读取BRANCH数据
		if ( strncmp (Line, BRANCH, 19) == 0 )
		{
			for ( j = 0, fgets (Line, 303, fptmp); j < Nbranch && (strncmp (Line, "-999", 4) != 0); j++, fgets (Line, 303, fptmp) )
			{
				initialize_BranchData (&(RawData->BranchData[j]), Line);
			}
		}
	}
	return;
}

void initialize_BusData (Bus_Type * bus, char * Line)
{
	printf ("%s", Line);
	return;
}

void initialize_BranchData (Branch_Type * branch, char * Line)
{
	printf ("%s", Line);
	return;
}