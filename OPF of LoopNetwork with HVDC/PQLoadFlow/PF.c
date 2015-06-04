#include <stdio.h>
#include <malloc.h>
#include "PowerFlow.h"
#define _CHECKPOINT_

int main (void)
{
	RawData_Type * RawData;		//定义一个指向原始数据结构体的指针
	//为原始数据分配内存
	RawData = (RawData_Type *)malloc (sizeof(RawData_Type));	
	allocate_memory_rawdata (RawData);

	ImportData (RawData);

#ifdef _CHECKPOINT_
	//检测原始BUS数据是否正常导入
	int i, j;
	for ( i = 0; i < Nbus;i++ )
	{
		printf ("%d %s %d %d %d %f %f %f %f %f %f %f %f %f %f %f %f %d\n",
			*RawData->BusData[i].BusNum,
			RawData->BusData[i].Name, 
			*RawData->BusData[i].LFarea,
			*RawData->BusData[i].LossZone, 
			*RawData->BusData[i].Type, 
			*RawData->BusData[i].Vol,
			*RawData->BusData[i].Deg, 
			*RawData->BusData[i].PL, 
			*RawData->BusData[i].QL,
			*RawData->BusData[i].PG, 
			*RawData->BusData[i].QG, 
			*RawData->BusData[i].BaseVol,
			*RawData->BusData[i].DesiredVol, 
			*RawData->BusData[i].MaxVol,
			*RawData->BusData[i].MinVol, 
			*RawData->BusData[i].ShuntG, 
			*RawData->BusData[i].ShuntB,
			*RawData->BusData[i].RemoteCtrlBus);
			
	}
	//检测原始BRANCH数据是否导入
	for ( j = 0; j < Nbranch; j++ )
	{
		printf ("%d %d %d %d %d %d %f %f %f %d %d %d %d %d %f %f %f %f %f %f %f\n",
			*RawData->BranchData[j].i, 
			*RawData->BranchData[j].j, 
			*RawData->BranchData[j].LFarea, 
			*RawData->BranchData[j].LossZone,
			*RawData->BranchData[j].Circuit,
			*RawData->BranchData[j].Type, 
			*RawData->BranchData[j].R, 
			*RawData->BranchData[j].X,
			*RawData->BranchData[j].B,
			*RawData->BranchData[j].LineRate1,
			*RawData->BranchData[j].LineRate2,
			*RawData->BranchData[j].LineRate3,
			*RawData->BranchData[j].CtrlBusNum,
			*RawData->BranchData[j].CtrlBusSide,
			*RawData->BranchData[j].K, 
			*RawData->BranchData[j].PhaseShifterDeg, 
			*RawData->BranchData[j].MinSorVol, 
			*RawData->BranchData[j].MaxTap,
			*RawData->BranchData[j].StepSize, 
			*RawData->BranchData[j].MinSorVol,
			*RawData->BranchData[j].MaxSorVol);
	}
#endif
	AdjacencyMat A;
	AdmittanceMat YMat;
	Mat C;
	InitMat (&C, Nbranch+Nbus, Nbranch+Nbus);
	A = CreatAdjacencyMatix (RawData);
	//YMat = CreatAdmittanceMatix (&A);
	//showMat (A->A_Re);
	//showMat (A->A_Im);
	//showMat (A->yb_Re);
	showMat (A->yb_Im);
	copyMat (A->yb_Im, &C);
	showMat (&C);
	//showMat (YMat->Y_Re);
	//showMat (YMat->Y_Im);
	getchar ();
	getchar ();
	return 0;
}		  

