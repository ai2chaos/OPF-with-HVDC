#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>	//bool类型源文件
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
	Elem * pCurrent;	//当前指针指向矩阵的首元素
	Elem * pNext;			//下一个元素地址

	//对新元素进行赋值
	pNew->VA = aij;
	pNew->IA = i;
	pNew->JA = j;

	//更新链表指针
	if ((*pMat)->HEAD == NULL)
	{
		//添加链表第一个元素
		(*pMat)->HEAD = pNew;
		pNew->NEXT = NULL;
		pCurrent = (*pMat)->HEAD;
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
		else if ( ((pCurrent->IA == i) && (pCurrent->JA < j)) || (pCurrent->IA < i) )
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
				( (pCurrent->IA < i) || ( (pCurrent->IA == i) && (pCurrent->JA < j) ) ) )
			{
				pCurrent->NEXT = pNew;
				pNew->NEXT = NULL;
				return true;
			}
		}
	}
	else
	{
		printf ("Can't add element A%d%d to matix", i, j);
		return false;
	}
}

bool removeElement (Mat * pMat, int i, int j)
{
	Elem * pCurrent, * pNext;

	pCurrent = (*pMat)->HEAD;
	if ((pCurrent->IA == i)&&(pCurrent->JA == j))
	{
		pNext = pCurrent->NEXT;
		free ((*pMat)->HEAD);	//释放矩阵的第一个元素aij
		if ( (*pMat)->HEAD != NULL )
		{
			printf ("Can't remove A%d%d\n", i, j);
			return false;
		}
		(*pMat)->HEAD = pNext;	//新矩阵中第一个元素为原矩阵中第二个元素
		return true;
	}
	else
	{
		while ( (pNext = pCurrent->NEXT) != NULL )
		{
			if (( pNext->IA == i ) && ( pNext->JA == j ))
			{
				pCurrent->NEXT = pNext->NEXT;
				free (pNext);
				if (pNext != NULL)
				{
					printf ("Can't remove A%d%d\n", i, j);
					return false;
				}
				break;
				return true;
			}
		}
	}
}

void showMat (Mat * pMat)
{
	Elem * pCurrent;
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