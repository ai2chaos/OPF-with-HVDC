#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>	//bool����Դ�ļ�
#include "sparsematrix.h"


void InitMat (Mat * pMat)
{
	*pMat = (SparseMat *)malloc(sizeof(SparseMat));//malloc�����½�ϡ�����ĵ�ַ
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
				printf ("addElement: Can't add element A%d%d to matix,maybe it already exists!!\n", i, j);
				return false;
			}
		}
		else
		{
			printf ("addElement: Can't add element A%d%d to matix,maybe it already exists!!\n", i, j);

			return false;
		}
	}
	else
	{
		printf ("addElement: Can't add element A%d%d to matix,maybe it already exists!!\n", i, j);

		return false;
	}
	printf ("addElement: Can't add element A%d%d to matix,maybe it already exists!!\n", i, j);

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
	//���������һ��Ԫ�ؼ�����Ԫ���Ƿ�ΪҪɾ��Ԫ��
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
		printf ("removeElement: Can't find A%d%d\n", i, j);
		return false;
	}
}

bool IsRomved (Mat * pMat)
{
	int Num;
	Elem * pCurrent;
	pCurrent = (*pMat)->HEAD;
	//���¼�������е��������������
	if ( pCurrent != NULL )
	{
		for ( Num = 1; pCurrent->NEXT != NULL; Num++ )
		{
			pCurrent = pCurrent->NEXT;
		}	
	}
	else
	{
		printf ("IsRemoved: Mat is empty!!\n");
		Num = 0;
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

double findElemValue (const Mat * pMat, int i, int j)
{
	Elem * pCurrent;
	double result = 0 ;
	pCurrent = (*pMat)->HEAD;
	while (pCurrent != NULL)
	{
		if ( pCurrent->IA == i && pCurrent->JA == j )
		{
			result = (double)pCurrent->VA;
			break;
		}
		else
			pCurrent = pCurrent->NEXT;
	}
	return result;
}

Mat * productMat (Mat * pMatA, Mat * pMatB)
{
	int n, m, iA, iB, jA, jB, k;
	double value, VA, VB;
	Mat pResult;	//�������ϡ�����ָ��
	InitMat (&pResult);
	
	iA = (*pMatA)->Ni;
	jA = (*pMatA)->Nj;
	iB = (*pMatB)->Ni;
	jB = (*pMatB)->Nj;
	if (jA == iB)
	{
		for ( n = 1; n <= iA; n++ )
		{
			for ( m = 1; m <= jB; m++ )
			{
				/*
				����C[n m]��value
				C[n m]=A[n 1]*B[1 m]+A[n 2]*B[2 m]+...+A[n k]*B[k m]
				k = jA = iB
				 */
				for ( k = 1; k <= jA; k++ )
				{
					//Ԫ�ص�ֵ��һ��Ϊ0��������ֱ��Ϊ0
					if ( ((VA = findElemValue (pMatA, n, k)) == 0) ||
						((VB = findElemValue (pMatB, k, m)) == 0) )
					{
						value += 0;
					}
					//���߶���Ϊ0���������˻��������ۼ�
					else
					{
						value += VA*VB;
					}
				}
				addElement (value, n, m, &pResult);
			}
		}
	}
	else
	{
		printf ("productMat: Matrix dimension mismatch!!");
		return NULL;
	}
}

void showMat (const Mat * pMat)
{
	Elem * pCurrent;
	int maxi, maxj, i, j;
	maxi = (*pMat)->Ni;
	maxj = (*pMat)->Nj;
	pCurrent = (*pMat)->HEAD;
	printf ("%8s %4s %4s\n", "Num", "Ni", "Nj");
	printf ("%8d %4d %4d\n", (*pMat)->NElement, (*pMat)->Ni, (*pMat)->Nj);
	//������ʾ��ʽ
	for ( i = 1; i <= maxi; i++ )
	{
		for ( j = 1; j <= maxj; j++ )
		{
			printf ("%8.2f", findElemValue (pMat, i, j));
		}
		printf ("\n");
	}
	/*��ֵ-�к�-�к� ��ʾ��ʽ
	while (pCurrent != NULL)
	{
		printf ("%8.2f %4d %4d\n", pCurrent->VA, pCurrent->IA, pCurrent->JA);
		pCurrent = pCurrent->NEXT;
	}
	*/
	return;
}