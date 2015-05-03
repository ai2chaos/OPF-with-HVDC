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
	sscanf (Line, "%4d %12[0-9A-Za-z- ] %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d",
		bus->BusNum, bus->Name, bus->LFarea, bus->LossZone, bus->Type, bus->Vol,
		bus->Deg, bus->PL, bus->QL, bus->PG, bus->QG,
		bus->BaseVol, bus->DesiredVol, bus->MaxVol, bus->MinVol, bus->ShuntG,
		bus->ShuntB, bus->RemoteCtrlBus);
	//���bus->typeȱ����ֵ����,�˴����Ͻ���һ��Ҫע�⵼���������ԭ�����Ƿ�һ��
	if ((*(bus->Type) == (1||0)) && (*(bus->Vol) <= 1))
	{
		*(bus->Vol) = *(bus->Vol) + *(bus->Type);
		*(bus->Type) = 0;
	}
	return;
}

void initialize_BranchData (Branch_Type * branch, char * Line)
{
	printf ("%s", Line);
	return;
}