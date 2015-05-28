#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "sparsematrix.h"

int main (void)
{
	//Ï¡Êè¾ØÕóÔªËØ
	/*
	int A[5][5];
	int i, j, k;
	Mat matA;
	InitMat (&matA, 3, 4);
	for ( i = 1, k = 1; i < 4; i++ )
	{
		for ( j = 1; j < 5; j++, k++ )
		{
			A[i][j] = k;
			addElement (A[i][j], i, j, &matA);
		}
	}
	showMat (&matA);  
	Mat matB;
	InitMat (&matB, 4, 3);
	for ( i = 1; i < 5; i++ )
	{
		for ( j = 1; j < 4; j++ )
		{
			if (i == j)
			{
				addElement (1, i, j, &matB);
			}
		}
	}
	addElement (2, 1, 3, &matB);
	showMat (&matB);
	Mat matAB;
	matAB = productMat (&matA, &matB);
	showMat (&matAB);
	*/
	Mat matA;
	LDU Test;
	InitMat (&matA, 4, 4);
	/*
	addElement (1, 1, 1, &matA);
	addElement (2, 1, 2, &matA);
	addElement (1, 1, 3, &matA);
	addElement (1, 1, 4, &matA);
	addElement (2, 2, 1, &matA);
	addElement (1, 2, 2, &matA);
	addElement (1, 3, 1, &matA);
	addElement (1, 3, 3, &matA);
	addElement (1, 4, 1, &matA);
	addElement (1, 4, 4, &matA);
	*/
	addElement (0.2368, 1, 1, &matA);
	addElement (0.2471, 1, 2, &matA);
	addElement (0.2568, 1, 3, &matA);
	addElement (1.2671, 1, 4, &matA);
	addElement (0.1968, 2, 1, &matA);
	addElement (0.2071, 2, 2, &matA);
	addElement (1.2168, 2, 3, &matA);
	addElement (0.2271, 2, 4, &matA);
	addElement (0.1581, 3, 1, &matA);
	addElement (1.1675, 3, 2, &matA);
	addElement (0.1768, 3, 3, &matA);
	addElement (0.1871, 3, 4, &matA);
	addElement (1.1161, 4, 1, &matA);
	addElement (0.1254, 4, 2, &matA);
	addElement (0.1397, 4, 3, &matA);
	addElement (0.1490, 4, 4, &matA);
	showMat (&matA);
	Test = CalFactorT (&matA);
	Mat B;
	InitMat (&B, 4, 1);
	addElement (2.8471, 1, 1, &B);
	addElement (2.7471, 2, 1, &B);
	addElement (2.6471, 3, 1, &B);
	addElement (2.5471, 4, 1, &B);
	/*
	addElement (-1, 1, 1, &B);
	addElement (1, 2, 1, &B);
	addElement (2, 3, 1, &B);
	*/
	showMat (&B);
	//showMat (&(Test->matU));
	//showMat (&(Test->matD));
	//showMat (&(Test->matL));
	Mat result;
	result = solveEqs (&Test, &B);
	showMat (&result);
	/*
	Mat C;
	C = minusMat (&matA, &matB);
	showMat (&C);
	LDU Afactor = CalFactorT (&matA);
	Mat E;
	Mat D;
	D = productK (&C, 3);
	showMat (&D);
	*/
	addElement (100, 2, 5, &result);
	showMat (&result);
	getchar ();
	getchar ();
	return 0;
}