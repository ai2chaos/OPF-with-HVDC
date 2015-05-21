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
	InitMat (&matA, 4, 4);
	addElement (2, 1, 1, &matA);
	addElement (7, 1, 2, &matA);
	addElement (-3, 1, 4, &matA);
	addElement (5, 2, 1, &matA);
	addElement (4, 2, 2, &matA);
	addElement (5, 3, 3, &matA);
	addElement (-2, 4, 2, &matA);
	addElement (6, 4, 4, &matA);
	showMat (&matA);
	CalFactorT (&matA);
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
	getchar ();
	getchar ();
	return 0;
}