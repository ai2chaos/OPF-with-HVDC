#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>	//bool����Դ�ļ�
#include "sparsematrix.h"


void InitMat (Mat * pMat)
{
	*pMat = (SparseMat *)malloc(sizeof(SparseMat));
	(*pMat)->HEAD = NULL;
	(*pMat)->NElement = 0;
	(*pMat)->Ni = 0;
	(*pMat)->Nj = 0;
	return;
}

void InitElem (Elem * pElem)
{
	pElem->VA = 0;
	pElem->JA = 0;
	pElem->NEXT = NULL;
	pElem->IA = 0;	//�������������Ա�ĳ�ʼ�����кŵ����������
	return;
}

bool MatIsEmpty (const Mat * pMat)
{
	if ( (*pMat)->HEAD == NULL )
		return true;
	else
		return false;
}

bool addElement (double aij, int i, int j, Mat * pMat)
{
	Elem * pNew;

	if ( (pNew = (Elem *)malloc (sizeof(Elem))) == NULL )
	{
		printf ("Problem allocating memory\n");
		return false;
	}
	else
	{
		InitElem (pNew);
		if ( addList (aij, i, j, pMat, pNew) )
		{

			(*pMat)->NElement += 1;

			if ((*pMat)->Ni < i)
			{
				(*pMat)->Ni = i;
			}

			if ((*pMat)->Nj < j)
			{
				(*pMat)->Nj = j;
			}
			return true;
		}
		else
			return false;
	}
}

bool addList (double aij, int i, int j, Mat * pMat, Elem * pNew)
{
	Elem * pCurrent;	//��ǰָ��ָ��������Ԫ��
	Elem * pNext;			//��һ��Ԫ�ص�ַ

	//����Ԫ�ؽ��и�ֵ
	pNew->VA = aij;
	pNew->IA = i;
	pNew->JA = j;

	//��������ָ��
	if ((*pMat)->HEAD == NULL)
	{
		//��������һ��Ԫ��
		(*pMat)->HEAD = pNew;
		pNew->NEXT = NULL;
		pCurrent = (*pMat)->HEAD;
		return true;
	}
	else if ( (*pMat)->HEAD != NULL )
	{
		//��������ͷ��Ԫ��
		pCurrent = (*pMat)->HEAD;
		if ( pCurrent->IA > i )
		{
			pNew->NEXT = pCurrent;
			(*pMat)->HEAD = pNew;
			return true;
		}
		else if ( (pCurrent->IA == i) && (pCurrent->JA > j) )
		{
			pNew->NEXT = pCurrent;
			(*pMat)->HEAD = pNew;
			return true;
		}
		else if ( ((pCurrent->IA == i) && (pCurrent->JA < j)) || (pCurrent->IA < i) )
		{
			//�������м����Ԫ��
			while ( (pNext = pCurrent->NEXT) != NULL )
			{
				//���в���
				if ( (pCurrent->IA == i) && (pNext->IA == i) )
				{
					if ( (pCurrent->JA < j) && (pNext->JA >j) )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//���ײ���
				else if ( (pCurrent->IA < i) && (pNext->IA == i) )
				{
					if ( pNext->JA > j )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//��β����
				else if ( (pCurrent->IA == i) && (pNext->IA > i) )
				{
					if ( pCurrent->JA < j )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//���м����
				else if ( (pCurrent->IA < i) && (pNext->IA > i) )
				{
					pCurrent->NEXT = pNew;
					pNew->NEXT = pNext;
					return true;
				}
				pCurrent = pCurrent->NEXT;
			}
			//������ĩβ���Ԫ��
			if ( (pNext == NULL) &&
				( (pCurrent->IA < i) || ( (pCurrent->IA == i) && (pCurrent->JA < j) ) ) )
			{
				pCurrent->NEXT = pNew;
				pNew->NEXT = NULL;
				return true;
			}
			else
			{
				printf ("Can't add element A%d%d to matix\n", i, j);
				return false;
			}
		}
		else
		{
			printf ("Can't add element A%d%d to matix\n", i, j);
			return false;
		}
	}
	else
	{
		printf ("Can't add element A%d%d to matix\n", i, j);
		return false;
	}
	printf ("Can't add element A%d%d to matix\n", i, j);
	return false;
}

bool removeElement (Mat * pMat, int i, int j)
{
	Elem * pCurrent, * pNext;
	bool flag = false;

	pCurrent = (*pMat)->HEAD;
	if ( (pCurrent->IA == i) && (pCurrent->JA == j) )	//�������һ��Ԫ���Ƿ�ΪҪɾ��Ԫ��
	{
		pNext = pCurrent->NEXT;
		free ((*pMat)->HEAD);	//�ͷž���ĵ�һ��Ԫ��aij
		(*pMat)->HEAD = pNext;	//�¾����е�һ��Ԫ��Ϊԭ�����еڶ���Ԫ��
		flag = true;
		
	}
	//else if ( (pCurrent->IA != i) || (pCurrent->JA != j) )	//���������һ��Ԫ�ؼ�����Ԫ���Ƿ�ΪҪɾ��Ԫ��
	else
	{
		while ( (pNext = pCurrent->NEXT) != NULL )
		{
			if ( ( pNext->IA == i ) && ( pNext->JA == j ) )
			{
				pCurrent->NEXT = pNext->NEXT;
				free (pNext);
				break;
			}
			pCurrent = pNext;
		}
		flag = true;
	}
	if (flag && IsRomved(pMat))
	{
		return true;
	}
	else
	{
		printf ("Can't find A%d%d\n", i, j);
		return false;
	}
}

bool IsRomved (Mat * pMat)
{
	int Num;
	Elem * pCurrent;
	pCurrent = (*pMat)->HEAD;
	//���¼�������е��������������
	for (Num = 1; pCurrent->NEXT != NULL; Num++)
	{
		pCurrent = pCurrent->NEXT;
	}
	//�жϾ������Ԫ��ʱ�����ɾ��ǰ��0����-1
	if ( Num == ((*pMat)->NElement-1) )
	{
		(*pMat)->NElement = Num;
		return true;
	}
	else
		return false;
}

void showMat (Mat * pMat)
{
	Elem * pCurrent;
	//int i, j;
	//i = (*pMat)->Ni;
	//j = (*pMat)->Nj;
	pCurrent = (*pMat)->HEAD;
	printf ("%8s %4s %4s\n", "Num", "Ni", "Nj");
	printf ("%8d %4d %4d\n", (*pMat)->NElement, (*pMat)->Ni, (*pMat)->Nj);
	while (pCurrent != NULL)
	{
		printf ("%8.2f %4d %4d\n", pCurrent->VA, pCurrent->IA, pCurrent->JA);
		pCurrent = pCurrent->NEXT;
	}
	return;
}