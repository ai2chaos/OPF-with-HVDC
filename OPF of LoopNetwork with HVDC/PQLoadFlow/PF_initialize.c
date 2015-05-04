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
		//读取BUS数据，并进行结构体赋值
		if ( strncmp (Line, BUS, 16) == 0 )
		{
			for ( i = 0, fgets (Line, 303, fptmp); i < Nbus && (strncmp (Line, "-999", 4) != 0); i++, fgets (Line, 303, fptmp) )
			{
				initialize_BusData (&(RawData->BusData[i]), Line);
			}
		}
		//读取BRANCH数据，并进行结构体赋值
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
	//printf ("%s", Line);	//检测是否能够正确读入.DATor.TXT
	sscanf (Line, "%4d %12[0-9A-Za-z- ] %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d",
		bus->BusNum, bus->Name, bus->LFarea, bus->LossZone, bus->Type, bus->Vol,
		bus->Deg, bus->PL, bus->QL, bus->PG, bus->QG,
		bus->BaseVol, bus->DesiredVol, bus->MaxVol, bus->MinVol, bus->ShuntG,
		bus->ShuntB, bus->RemoteCtrlBus);
	//解决bus->type缺少数值问题,此处不严谨，一定要注意导入的数据与原数据是否一致
	if ((*(bus->Type) == (1||0)) && (*(bus->Vol) <= 1))
	{
		*(bus->Vol) = *(bus->Vol) + *(bus->Type);
		*(bus->Type) = 0;
	}
	return;
}

void initialize_BranchData (Branch_Type * branch, char * Line)
{
	//printf ("%s", Line);	//检测是否能够正确读入.DATor.TXT
	sscanf (Line, "%d %d %d %d %d %d %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f", 
		branch->i, branch->j, branch->LFarea, branch->LossZone, branch->Circuit,
		branch->Type, branch->R, branch->X, branch->B, branch->LineRate1, branch->LineRate2,
		branch->LineRate3, branch->CtrlBusNum, branch->CtrlBusSide, branch->K,
		branch->PhaseShifterDeg, branch->MinTap, branch->MaxTap, branch->StepSize,
		branch->MinSorVol, branch->MaxSorVol);
	//Branch.Type位置不能为空格
	return;
}