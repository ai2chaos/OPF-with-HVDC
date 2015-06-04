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

	//���ɾ������Y=(A_Re+jA_Im)(yb_Re+jyb_Im)(A_ReT+jA_ImT)
	//���㵼�ɾ����ʵ�������ڽӾ����в����鲿ʱ��
	tempMatARyR = productMat ((*A)->A_Re, (*A)->yb_Re);
	tempMatARyRART = productMat (&tempMatARyR, &A_ReT);	//AR*yR*ART
	//���㵼�ɾ�����鲿�����ڽӾ����в����鲿ʱ��
	tempMatARyI = productMat ((*A)->A_Re, (*A)->yb_Im);
	tempMatARyIART = productMat (&tempMatARyI, &A_ReT);	//AR*yI*ART
	//�ͷ�tempMatA��tempMatB��ָ��Ķ�̬�ڴ�ռ�
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
		//�����ڽӾ������鲿ʱ�ĵ��ɾ���ʵ�����鲿
		A_ImT = TransposeMat ((*A)->A_Im);
		tempMatAIyR = productMat ((*A)->A_Im, (*A)->yb_Re);
		tempMatAIyI = productMat ((*A)->A_Im, (*A)->yb_Im);
		tempMatARyIAIT = productMat (&tempMatARyI, &A_ImT);	//AR*yI*AIT
		tempMatAIyRAIT = productMat (&tempMatAIyR, &A_ImT);	//AI*yR*AIT
		tempMatAIyIART = productMat (&tempMatAIyI, &A_ReT);	//AI*yI*ART
		tempMatARyRAIT = productMat (&tempMatARyR, &A_ImT);	//AR*yR*AIT
		tempMatAIyRART = productMat (&tempMatAIyR, &A_ReT);	//AI*yR*ART
		tempMatAIyIAIT = productMat (&tempMatAIyI, &A_ImT);	//AI*yI*AIT
		//ʵ��׷��
		tempMatA = minusMat (&tempMatARyRART, &tempMatAIyIART);
		tempMatB = minusMat (&tempMatA, &tempMatAIyRAIT);
		deallocateMemoryMat (&tempMatA);
		tempMatA = minusMat (&tempMatB, &tempMatARyIAIT);
		result->Y_Re = &tempMatA;
		deallocateMemoryMat (&tempMatB);
		//�鲿׷��
		tempMatA = minusMat (&tempMatARyIART, &tempMatAIyIAIT);
		tempMatB = addMat (&tempMatA, &tempMatAIyRART);
		deallocateMemoryMat (&tempMatA);
		tempMatA = addMat (&tempMatB, &tempMatARyRAIT);
		result->Y_Im = &tempMatA;
		deallocateMemoryMat (&tempMatB);

		//�ͷ���ʱ����
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