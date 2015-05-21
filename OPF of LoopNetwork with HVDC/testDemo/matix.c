#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>	//bool����Դ�ļ�
#include "sparsematrix.h"

/************************************************************************/
/* tips:																*/
/*		1.ע�����ָ��Ϊ�պͿ�ϡ����󣨲�����0Ԫ�ص����Ѿ���ʼ����������!!*/
/*      2.��ĳЩ�������ʧ��ʱ�������½��ġ��Ѿ���ʼ���Ŀ�ϡ�����         */
/*      3.�������к���������˴����ϡ�����ָ���Ƿ�Ϊ�գ���Ҫ�Ľ�         */
/************************************************************************/


/************************************************************************/
/*                         �����������                                  */
/************************************************************************/
void InitMat (Mat * pMat, int n, int m)
{
	*pMat = (SparseMat *)malloc(sizeof(SparseMat));
	//malloc�����½�ϡ�����ĵ�ַ
	(*pMat)->HEAD = NULL;
	(*pMat)->NElement = 0;
	(*pMat)->Ni = n;
	(*pMat)->Nj = m;
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
	//������Ԫ���Ƿ񳬹�����ά��
	if ( i > (*pMat)->Ni || j > (*pMat)->Nj)
	{
		printf ("addList: Elements of the %d row or %d column number exceeds matrix dimensions!!\n", i, j);
		return false;
	}

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
		else if ( ((pCurrent->IA == i) && (pCurrent->JA < j)) ||
			(pCurrent->IA < i) )
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
				( (pCurrent->IA < i) ||
				( (pCurrent->IA == i) && (pCurrent->JA < j) ) ) )
			{
				pCurrent->NEXT = pNew;
				pNew->NEXT = NULL;
				return true;
			}
			else
			{
				printf ("addElement: Can't add element A%d%d to matix, maybe it already exists!!\n", i, j);
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
	if ( (pCurrent->IA == i) && (pCurrent->JA == j) )	
		//�������һ��Ԫ���Ƿ�ΪҪɾ��Ԫ��
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
	//�ж��Ƿ�ɾ��
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

bool IsRomved (const Mat * pMat)
{
	int Num;
	Elem * pCurrent;
	pCurrent = (*pMat)->HEAD;
	//���¼�������з�0Ԫ�ظ���
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
Mat TransposeMat (const Mat * pMatA)
{
	Elem * pCurrent;
	Mat pResult;
	InitMat (&pResult, (*pMatA)->Nj, (*pMatA)->Ni);

	if ( *pMatA != NULL )
	{
		pCurrent = (*pMatA)->HEAD;
		while ( pCurrent != NULL)
		{
			addElement (pCurrent->VA, pCurrent->JA, pCurrent->IA, &pResult);
			pCurrent = pCurrent->NEXT;
		}
		return pResult;
	}
	else
	{
		printf ("TransposeMat: Matix is Empty!!\n ");
		return pResult;
	}
}

Mat productK (const Mat * pMatA, double K)
{
	Elem * pCurrent;
	Mat pResult;
	if ( *pMatA != NULL && K !=0 )	//������ָ���Ƿ�Ϊ��
	{
		pCurrent = (*pMatA)->HEAD;
		InitMat (&pResult, (*pMatA)->Ni, (*pMatA)->Nj);
		while ( pCurrent != NULL )
		{
			addElement (K*pCurrent->VA, pCurrent->IA, pCurrent->JA, &pResult);
			pCurrent = pCurrent->NEXT;
		}
		return pResult;
	}
	else
	{
		printf ("productK: Matix is Empty!!\n ");
		InitMat (&pResult, 1, 1);
		return pResult;	//�˴����صľ��󲻺��з�0Ԫ�أ�����ָ�벻ΪNULL	
	}
	
}

Mat productMat (const Mat * pMatA, const Mat * pMatB)
{
	int n, m, iA, iB, jA, jB, k;
	double value, VA, VB;
	Mat pResult;	//�������ϡ�����ָ��
	iA = (*pMatA)->Ni;
	jA = (*pMatA)->Nj;
	iB = (*pMatB)->Ni;
	jB = (*pMatB)->Nj;

	InitMat (&pResult, iA, jB);

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
				for ( k = 1, value = 0; k <= jA; k++ )
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
						value += VA*VB;	//+=����ǰҪ�ǵ��ȶ�value���г�ʼ��
					}
				}
				if ( value != 0 )
					addElement (value, n, m, &pResult);
				else
					continue;
			}
		}
		return pResult;
	}
	else
	{
		printf ("productMat: Matrix dimension mismatch!!\n");
		return pResult;	//�˴����صľ��󲻺��з�0Ԫ�أ�����ָ�벻ΪNULL
	}
}

Mat addMat (const Mat * pMatA, const Mat * pMatB)
{
	int n, m, iA, iB, jA, jB;
	double value, VA, VB;
	Mat pResult;	//�������ϡ�����ָ��
	iA = (*pMatA)->Ni;
	jA = (*pMatA)->Nj;
	iB = (*pMatB)->Ni;
	jB = (*pMatB)->Nj;

	InitMat (&pResult, iA, jB);

	if ( iA == iB && jA == jB )
	{
		for ( n = 1; n <= iA; n++ )
		{
			for ( m = 1, value = 0; m <= jA; m++ )
			{
				/*
				����C[n m]��value
				C[n m]=A[n m]+B[n m]
				*/
				if ( ((VA = findElemValue (pMatA, n, m)) == 0) &
					((VB = findElemValue (pMatB, n, m)) == 0) )	
					//��Ҫ��&&������ж�·���ʣ�������һ�����ʽû�м���
				{
					value = 0;
				}
				//���߶���Ϊ0
				else
				{
					value = VA + VB;	//����ǰҪ�ǵ��ȶ�value���г�ʼ��
				}
				if ( value != 0 )
					addElement (value, n, m, &pResult);
				else
					continue;
			}
		}
    	return pResult;
	}
	else
	{
		printf ("addMat: Matrix dimension mismatch!!\n");
		return pResult;	//�˴����صľ��󲻺��з�0Ԫ�أ�����ָ�벻ΪNULL
	}
}

Mat minusMat (const Mat * pMatA, const Mat * pMatB)
{
	Mat pResult, pMatNB;
	pMatNB = productK (pMatB, -1);
	pResult = addMat (pMatA, &pMatNB);
	return pResult;
}

void showMat (const Mat * pMat)
{
	Elem * pCurrent;
	int maxi, maxj, i, j;
	if ( *pMat != NULL )
	{
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
		//��ֵ-�к�-�к� ��ʾ��ʽ
		/*
		while (pCurrent != NULL)
		{
		printf ("%8.2f %4d %4d\n", pCurrent->VA, pCurrent->IA, pCurrent->JA);
		pCurrent = pCurrent->NEXT;
		}
		*/
		return;
	}
	else
	{
		printf ("ShowMat: This is an empty pMat!!\n");
		return;
	}
}

/************************************************************************/
/*                       ���Է��������                                  */
/************************************************************************/

LDU CalFactorT (Mat * pMat)
{
	int n, m, i, j, p;
	double Vpj1, Vpj2, Vpp, Vij1, Vij2, Vip;
	//���pMatָ���Ƿ�Ϊ��
	if ( pMat == NULL )
	{
		printf ("CalFactorT: This is an empty pMat!!\n");
		return NULL;
	}
	//�������Ƿ�Ϊ��
	else if (MatIsEmpty (pMat))
	{
		printf ("CalFactorT: Matix is empty!!\n");
		return NULL;
	}
	else
	{
		n = (*pMat)->Ni;
		m = (*pMat)->Nj;
		if ( n != m )
		{
			printf ("CalFactorT: Matix is [%d %d], can't calculate FactorTable", n, m);
			return NULL;
		}
		else
		{
			//��ʼ��LDU���ӱ�ָ�뼰��ָ������ӱ�
			LDU factorTable;
			factorTable = (matLDU *)malloc (sizeof(matLDU));
			Mat matL, matD, matU;

			//��ʼ�����ӱ��е�ϡ�����
			InitMat (&matL, n, m);
			InitMat (&matD, n, m);
			InitMat (&matU, n, m);

			//��LDU���ӱ��и�ϡ�������и�ֵ
			factorTable->matL = matL;
			factorTable->matD = matD;
			factorTable->matU = matU;

			//���ӱ���L��D��U������⼰��ֵ
			/*
			for ( p = 1; p <= n - 1; p++ )
			{
				for ( j = p + 1; j <= m; j++ )
				{
					if ( (Vpp = findElemValue (pMat, p, p)) != 0 )
					{
						if ( (Vpj1 = findElemValue (pMat, p, j)) != 0 )
						{
							Vpj2 = Vpj1 / Vpp;
						}
						else
							Vpj2 = 0;
					}
					else
						printf ("CalFactorT: Division by zero!!\n");
					for ( i = p + 1; i <= n; i++ )
					{
						if ( (Vij1 = findElemValue (pMat, i, j)) != 0 &
							(Vip = findElemValue (pMat, i, j)) != 0 )
						{
							Vij2 = Vij1 - Vip*Vpj2;
						}
						else
							Vij2 = 0;
					}
				}
			}

			*/
			return factorTable;
		}
	}
}