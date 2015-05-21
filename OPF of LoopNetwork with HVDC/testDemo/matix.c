#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>	//bool类型源文件
#include "sparsematrix.h"

/************************************************************************/
/* tips:																*/
/*		1.注意矩阵指针为空和空稀疏矩阵（不含非0元素但是已经初始化）的区别!!*/
/*      2.当某些矩阵计算失败时，返回新建的、已经初始化的空稀疏矩阵         */
/*      3.不是所有函数都检测了传入的稀疏矩阵指针是否为空，需要改进         */
/************************************************************************/


/************************************************************************/
/*                         矩阵基本操作                                  */
/************************************************************************/
void InitMat (Mat * pMat, int n, int m)
{
	*pMat = (SparseMat *)malloc(sizeof(SparseMat));
	//malloc返回新建稀疏矩阵的地址
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
	pElem->IA = 0;	//对伸缩型数组成员的初始化，行号等于数组序号
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
	Elem * pCurrent;	//当前指针指向矩阵的首元素
	Elem * pNext;			//下一个元素地址

	//对新元素进行赋值
	pNew->VA = aij;
	pNew->IA = i;
	pNew->JA = j;
	//检测添加元素是否超过矩阵维度
	if ( i > (*pMat)->Ni || j > (*pMat)->Nj)
	{
		printf ("addList: Elements of the %d row or %d column number exceeds matrix dimensions!!\n", i, j);
		return false;
	}

	//更新链表指针
	if ((*pMat)->HEAD == NULL)
	{
		//添加链表第一个元素
		(*pMat)->HEAD = pNew;
		pNew->NEXT = NULL;
		pCurrent = (*pMat)->HEAD;
		return true;
	}
	else if ( (*pMat)->HEAD != NULL )
	{
		//更改链表头部元素
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
			//向链表中间插入元素
			while ( (pNext = pCurrent->NEXT) != NULL )
			{
				//行中插入
				if ( (pCurrent->IA == i) && (pNext->IA == i) )
				{
					if ( (pCurrent->JA < j) && (pNext->JA >j) )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//行首插入
				else if ( (pCurrent->IA < i) && (pNext->IA == i) )
				{
					if ( pNext->JA > j )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//行尾插入
				else if ( (pCurrent->IA == i) && (pNext->IA > i) )
				{
					if ( pCurrent->JA < j )
					{
						pCurrent->NEXT = pNew;
						pNew->NEXT = pNext;
						return true;
					}
				}
				//两行间插入
				else if ( (pCurrent->IA < i) && (pNext->IA > i) )
				{
					pCurrent->NEXT = pNew;
					pNew->NEXT = pNext;
					return true;
				}
				pCurrent = pCurrent->NEXT;
			}
			//向链表末尾添加元素
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
		//检测矩阵第一个元素是否为要删除元素
	{
		pNext = pCurrent->NEXT;
		free ((*pMat)->HEAD);	//释放矩阵的第一个元素aij
		(*pMat)->HEAD = pNext;	//新矩阵中第一个元素为原矩阵中第二个元素
		flag = true;
		
	}
	//检测除矩阵第一个元素及最后个元素是否为要删除元素
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
	//判断是否删除
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
	//重新计算矩阵中非0元素个数
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
	//判断矩阵非零元素时候等于删除前非0个数-1
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
	if ( *pMatA != NULL && K !=0 )	//检测矩阵指针是否为空
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
		return pResult;	//此处返回的矩阵不含有非0元素，但其指针不为NULL	
	}
	
}

Mat productMat (const Mat * pMatA, const Mat * pMatB)
{
	int n, m, iA, iB, jA, jB, k;
	double value, VA, VB;
	Mat pResult;	//创建结果稀疏矩阵指针
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
				计算C[n m]的value
				C[n m]=A[n 1]*B[1 m]+A[n 2]*B[2 m]+...+A[n k]*B[k m]
				k = jA = iB
				 */
				for ( k = 1, value = 0; k <= jA; k++ )
				{
					//元素的值有一个为0则二者相乘直接为0
					if ( ((VA = findElemValue (pMatA, n, k)) == 0) ||
						((VB = findElemValue (pMatB, k, m)) == 0) )
					{
						value += 0;
					}
					//二者都不为0，则计算其乘积并进行累加
					else
					{
						value += VA*VB;	//+=运算前要记得先对value进行初始化
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
		return pResult;	//此处返回的矩阵不含有非0元素，但其指针不为NULL
	}
}

Mat addMat (const Mat * pMatA, const Mat * pMatB)
{
	int n, m, iA, iB, jA, jB;
	double value, VA, VB;
	Mat pResult;	//创建结果稀疏矩阵指针
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
				计算C[n m]的value
				C[n m]=A[n m]+B[n m]
				*/
				if ( ((VA = findElemValue (pMatA, n, m)) == 0) &
					((VB = findElemValue (pMatB, n, m)) == 0) )	
					//不要用&&，其具有短路性质，导致另一个表达式没有计算
				{
					value = 0;
				}
				//二者都不为0
				else
				{
					value = VA + VB;	//运算前要记得先对value进行初始化
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
		return pResult;	//此处返回的矩阵不含有非0元素，但其指针不为NULL
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
		//矩阵显示形式
		for ( i = 1; i <= maxi; i++ )
		{
			for ( j = 1; j <= maxj; j++ )
			{
				printf ("%8.2f", findElemValue (pMat, i, j));
			}
			printf ("\n");
		}
		//数值-行号-列号 显示形式
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
/*                       线性方程组求解                                  */
/************************************************************************/

LDU CalFactorT (Mat * pMat)
{
	int n, m, i, j, p;
	double Vpj1, Vpj2, Vpp, Vij1, Vij2, Vip;
	//检测pMat指针是否为空
	if ( pMat == NULL )
	{
		printf ("CalFactorT: This is an empty pMat!!\n");
		return NULL;
	}
	//检测矩阵是否为空
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
			//初始化LDU因子表指针及其指向的因子表
			LDU factorTable;
			factorTable = (matLDU *)malloc (sizeof(matLDU));
			Mat matL, matD, matU;

			//初始化因子表中的稀疏矩阵
			InitMat (&matL, n, m);
			InitMat (&matD, n, m);
			InitMat (&matU, n, m);

			//对LDU因子表中个稀疏矩阵进行赋值
			factorTable->matL = matL;
			factorTable->matD = matD;
			factorTable->matU = matU;

			//因子表中L、D、U矩阵求解及赋值
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