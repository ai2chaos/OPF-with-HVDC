#include <math.h>
#include <stdio.h>

#include "PowerFlow.h"

AdjacencyMat CreatAdjacencyMatix (RawData_Type * RawData)
{
	AdjacencyMat result;
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

	return result;
}