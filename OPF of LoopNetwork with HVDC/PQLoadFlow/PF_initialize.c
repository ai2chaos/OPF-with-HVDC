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
	rewind (fptmp);		//�ص��ļ�ͷ������������ļ�ָ�볬���ļ���Χ,�γ�����
	while ( fgets (Line, 303, fptmp) != NULL )
	{
		//��ȡbus����
		if ( strncmp (Line, BUS, 16) == 0 )
		{
			for ( i = 0, fgets (Line, 303, fptmp); i < Nbus && (strncmp (Line, "-999", 4) != 0); i++, fgets (Line, 303, fptmp) )
			{
				initialize_BusData (&(RawData->BusData[i]), Line);
			}
		}
		//��ȡBRANCH����
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