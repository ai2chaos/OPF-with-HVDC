#include <math.h>
#include <stdio.h>

#include "PowerFlow.h"

#define PI 3.14159

AdjacencyMat CreatAdjacencyMatix (const RawData_Type * RawData)
{
	AdjacencyMat result;
	double Fi, Fj, Bi, Bj, k, deg, R, X, G, B, absZ;
	//�������ڴ棺
	result = (AdjacencyMat_type *)malloc (sizeof (AdjacencyMat_type));
	result->A_Re = (Mat *)malloc (sizeof (Mat));
	result->A_Im = (Mat *)malloc (sizeof (Mat));
	result->yb_Re = (Mat *)malloc (sizeof (Mat));
	result->yb_Im = (Mat *)malloc (sizeof (Mat));
	//��ʼ��ϡ�����
	InitMat (result->A_Re, Nbus, Nbranch + Nbus);
	InitMat (result->A_Im, Nbus, Nbranch + Nbus);
	//�ڽӾ����ǰNbranch�м�¼���ڵ��֧·��Ϣ����Nbus�м�¼�Ե�֧·��Ϣ
	InitMat (result->yb_Re, Nbranch + Nbus, Nbranch + Nbus);
	InitMat (result->yb_Im, Nbranch + Nbus, Nbranch + Nbus);
	//֧·�����ǰNbranch�м�¼���ڵ��֧·��Ϣ����Nbus�м�¼�Ե�֧·��Ϣ
	//��֧·�䲻���л���ʱ��Ϊ�Խ���

	//�γ��ڽӾ���ͬʱ�γ�֧·���ɾ���

	int i;
	//׷�������·֧·����ѹ��֧·
	for ( i = 1; i <= Nbranch; i++ )
	{
		if ( *RawData->BranchData[i-1].Type == 0 )
		{
			if ( (*RawData->BranchData[i-1].K == 0) & 
				(*RawData->BranchData[i-1].PhaseShifterDeg == 0))
			{
				addElement (1, *RawData->BranchData[i-1].i, i, result->A_Re);
				addElement (-1, *RawData->BranchData[i - 1].j, i, result->A_Re);

			}
			else 
			{
				k = (double)*RawData->BranchData[i-1].K;
				deg = (double)*RawData->BranchData[i-1].PhaseShifterDeg;
				//Ĭ�ϱ�ѹ��������׶�
				addElement (1/(k*cos(deg*PI/180)), *RawData->BranchData[i-1].i, i, result->A_Re);
				addElement (-1, *RawData->BranchData[i-1].j, i, result->A_Re);
				//��������֧·
				if (deg != 0)
				{
					addElement (1 / (k*sin (deg*PI / 180)), *RawData->BranchData[i-1].i, i, result->A_Im);
				}
			}
			//����֧·����
			R = (double)*RawData->BranchData[i - 1].R;
			X = (double)*RawData->BranchData[i - 1].X;
			absZ = (pow (R, 2) + pow (X, 2));
			addElement (R / absZ, i, i, result->yb_Re);
			addElement (-X / absZ, i, i, result->yb_Im);
		}
	}
	//׷�ӶԵ�֧·
	for ( i = 1; i <= Nbus; i++ )
	{
		if (*RawData->BusData[i-1].ShuntB != 0 || *RawData->BusData[i-1].ShuntG != 0)
		{
			addElement (1, i, Nbranch + i, result->A_Re);
			//����Ե�֧·����
			B = (double)*RawData->BusData[i-1].ShuntB;
			G = (double)*RawData->BusData[i-1].ShuntG;
			addElement (G, Nbranch + i, Nbranch + i, result->yb_Re);
			addElement (B, Nbranch + i, Nbranch + i, result->yb_Im);
			G += findElemValue (result->yb_Re, Nbranch + i, Nbranch + i);
			B += findElemValue (result->yb_Im, Nbranch + i, Nbranch + i);
		}
	}
	for ( i = 1; i <= Nbranch; i++ )
	{
		if ( *RawData->BranchData[i-1].Type == 0 )
		{
			if ( *RawData->BranchData[i-1].B != 0 )
			{
				Fi = findElemValue (result->A_Re, *RawData->BranchData[i-1].i, *RawData->BranchData[i-1].i + Nbranch);
				Fj = findElemValue (result->A_Re, *RawData->BranchData[i-1].j, *RawData->BranchData[i-1].j + Nbranch);
				if ( Fi == 0 )
				{
					addElement (1, *RawData->BranchData[i-1].i, *RawData->BranchData[i-1].i + Nbranch, result->A_Re);
				}
				if ( Fj == 0 )
				{
					addElement (1, *RawData->BranchData[i-1].j, *RawData->BranchData[i-1].j + Nbranch, result->A_Re);
				}
				//׷�������·֧·�Եص���
				B = (double)*RawData->BranchData[i-1].B;
				Bi = findElemValue (result->yb_Im, *RawData->BranchData[i-1].i+Nbranch, *RawData->BranchData[i-1].i + Nbranch);
				Bj = findElemValue (result->yb_Im, *RawData->BranchData[i-1].j+Nbranch, *RawData->BranchData[i-1].j + Nbranch);
				Bi += 0.5*B;
				Bj += 0.5*B;
				updateElement (Bi, *RawData->BranchData[i-1].i + Nbranch, *RawData->BranchData[i-1].i + Nbranch, result->yb_Im);
				updateElement (Bj, *RawData->BranchData[i-1].j + Nbranch, *RawData->BranchData[i-1].j + Nbranch, result->yb_Im);
			}
		}
		

	}
	return result;
}