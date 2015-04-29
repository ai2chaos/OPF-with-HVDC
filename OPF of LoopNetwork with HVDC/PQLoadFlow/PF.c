#include <stdio.h>
#include <malloc.h>
#include "PowerFlow.h"
#define _CHECKPOINT_

int main (void)
{
	//char DataName[20];
	//printf ("Please enter the Power Flow Data name:");
	//scanf (" %s", DataName);
	RawData_Type * RawData;
	RawData = (RawData_Type *)malloc (sizeof(RawData_Type));
	allocate_memory_rawdata (RawData);
	ImportData (RawData);

#ifdef _CHECKPOINT_
	//检测原始BUS数据是否正常导入
	int i, j;
	for ( i = 0; i < Nbus;i++ )
	{
		printf ("%d %s %d\n", *RawData->BusData[i].BusNum, RawData->BusData[i].Name, 
			*RawData->BusData[i].LFarea);
		/*
		printf ("%d %s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d\n",
			RawData->BusData[i].BusNum, RawData->BusData[i].Name, RawData->BusData[i].LFarea,
			RawData->BusData[i].LossZone, RawData->BusData[i].Type, RawData->BusData[i].Vol,
			RawData->BusData[i].Deg, RawData->BusData[i].PL, RawData->BusData[i].QL,
			RawData->BusData[i].PG, RawData->BusData[i].QG, RawData->BusData[i].BaseVol,
			RawData->BusData[i].DesiredVol, RawData->BusData[i].MaxVol,
			RawData->BusData[i].MinVol, RawData->BusData[i].ShuntG, RawData->BusData[i].ShuntB,
			RawData->BusData[i].RemoteCtrlBus);
			*/
	}
	/*
	//检测原始BRANCH数据是否导入
	for ( j = 0; j < Nbranch; j++ )
	{
		printf ("%d %s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d",
			RawData->BusData[j].BusNum, RawData->BusData[j].Name, RawData->BusData[j].LFarea,
			RawData->BusData[i].LossZone, RawData->BusData[i].Type, RawData->BusData[i].Vol,
			RawData->BusData[i].Deg, RawData->BusData[i].PL, RawData->BusData[i].QL,
			RawData->BusData[i].PG, RawData->BusData[i].QG, RawData->BusData[i].BaseVol,
			RawData->BusData[i].DesiredVol, RawData->BusData[i].MaxVol,
			RawData->BusData[i].MinVol, RawData->BusData[i].ShuntG, RawData->BusData[i].ShuntB,
			RawData->BusData[i].RemoteCtrlBus);
	}
	*/
#endif
	getchar ();
	getchar ();
	return 0;
}		  

