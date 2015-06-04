#include <math.h>
#include <stdio.h>

#include "PowerFlow.h"

AdmittanceMat CreatAdmittanceMatix (const AdjacencyMat * A)
{
	AdmittanceMat result;
	result = (AdmittanceMat_type *)malloc (sizeof(AdmittanceMat_type));
	result->Y_Re = (Mat *)malloc (sizeof (Mat));
	result->Y_Im = (Mat *)malloc (sizeof (Mat));
	InitMat (result->Y_Re, Nbus, Nbus);
	InitMat (result->Y_Im, Nbus, Nbus);
	Mat A_ReT, A_ImT, tempMatARyR, tempMatARyI, tempMatAIyR, tempMatAIyI;
	Mat tempMatARyRART, tempMatARyIART, tempMatAIyRART, tempMatAIyIART;
	Mat tempMatARyRAIT, tempMatARyIAIT, tempMatAIyRAIT, tempMatAIyIAIT;
	Mat tempMatA, tempMatB;
	A_ReT = TransposeMat ((*A)->A_Re);

	//导纳矩阵求解Y=(A_Re+jA_Im)(yb_Re+jyb_Im)(A_ReT+jA_ImT)
	//计算导纳矩阵的实部（当邻接矩阵中不含虚部时）
	tempMatARyR = productMat ((*A)->A_Re, (*A)->yb_Re);
	tempMatARyRART = productMat (&tempMatARyR, &A_ReT);	//AR*yR*ART
	//计算导纳矩阵的虚部（当邻接矩阵中不含虚部时）
	tempMatARyI = productMat ((*A)->A_Re, (*A)->yb_Im);
	tempMatARyIART = productMat (&tempMatARyI, &A_ReT);	//AR*yI*ART
	//释放tempMatA，tempMatB所指向的动态内存空间
	if ( (*(*A)->A_Im)->NElement == 0 )
	{
		deallocateMemoryMat (&A_ReT);
		deallocateMemoryMat (&tempMatARyR);
		deallocateMemoryMat (&tempMatARyI);
		result->Y_Re = &tempMatARyRART;
		result->Y_Im = &tempMatARyIART;
		return result;
	}
	else
	{
		//计算邻接矩阵含有虚部时的导纳矩阵实部与虚部
		A_ImT = TransposeMat ((*A)->A_Im);
		tempMatAIyR = productMat ((*A)->A_Im, (*A)->yb_Re);
		tempMatAIyI = productMat ((*A)->A_Im, (*A)->yb_Im);
		tempMatARyIAIT = productMat (&tempMatARyI, &A_ImT);	//AR*yI*AIT
		tempMatAIyRAIT = productMat (&tempMatAIyR, &A_ImT);	//AI*yR*AIT
		tempMatAIyIART = productMat (&tempMatAIyI, &A_ReT);	//AI*yI*ART
		tempMatARyRAIT = productMat (&tempMatARyR, &A_ImT);	//AR*yR*AIT
		tempMatAIyRART = productMat (&tempMatAIyR, &A_ReT);	//AI*yR*ART
		tempMatAIyIAIT = productMat (&tempMatAIyI, &A_ImT);	//AI*yI*AIT
		//实部追加
		tempMatA = minusMat (&tempMatARyRART, &tempMatAIyIART);
		tempMatB = minusMat (&tempMatA, &tempMatAIyRAIT);
		deallocateMemoryMat (&tempMatA);
		tempMatA = minusMat (&tempMatB, &tempMatARyIAIT);
		result->Y_Re = &tempMatA;
		deallocateMemoryMat (&tempMatB);
		//虚部追加
		tempMatA = minusMat (&tempMatARyIART, &tempMatAIyIAIT);
		tempMatB = addMat (&tempMatA, &tempMatAIyRART);
		deallocateMemoryMat (&tempMatA);
		tempMatA = addMat (&tempMatB, &tempMatARyRAIT);
		result->Y_Im = &tempMatA;
		deallocateMemoryMat (&tempMatB);

		//释放临时矩阵
		deallocateMemoryMat (&tempMatARyR);
		deallocateMemoryMat (&tempMatARyI);
		deallocateMemoryMat (&tempMatAIyR);
		deallocateMemoryMat (&tempMatAIyI);
		deallocateMemoryMat (&tempMatARyRART);
		deallocateMemoryMat (&tempMatARyIAIT);
		deallocateMemoryMat (&tempMatAIyRAIT);
		deallocateMemoryMat (&tempMatAIyIART);
		deallocateMemoryMat (&tempMatARyRAIT);
		deallocateMemoryMat (&tempMatARyIART);
		deallocateMemoryMat (&tempMatAIyRART);
		deallocateMemoryMat (&tempMatAIyIAIT);
		deallocateMemoryMat (&A_ReT);
		deallocateMemoryMat (&A_ImT);
		return result;
	}
}