#include <math.h>
#include <stdio.h>

#include "PowerFlow.h"

AdjacencyMat CreatAdjacencyMatix (RawData_Type * RawData)
{
	AdjacencyMat result;
	//逐层分配内存：
	result = (AdjacencyMat_type *)malloc (sizeof (AdjacencyMat_type));
	result->A_Re = (Mat *)malloc (sizeof (Mat));
	result->A_Im = (Mat *)malloc (sizeof (Mat));
	result->yb_Re = (Mat *)malloc (sizeof (Mat));
	result->yb_Im = (Mat *)malloc (sizeof (Mat));
	//初始化稀疏矩阵
	InitMat (result->A_Re, Nbus, Nbranch + Nbus);
	InitMat (result->A_Im, Nbus, Nbranch + Nbus);
	//邻接矩阵的前Nbranch列记录两节点间支路信息，后Nbus列记录对地支路信息
	InitMat (result->yb_Re, Nbranch + Nbus, Nbranch + Nbus);
	InitMat (result->yb_Im, Nbranch + Nbus, Nbranch + Nbus);
	//支路矩阵的前Nbranch列记录两节点间支路信息，后Nbus列记录对地支路信息
	//当支路间不含有互感时其为对角阵

	return result;
}