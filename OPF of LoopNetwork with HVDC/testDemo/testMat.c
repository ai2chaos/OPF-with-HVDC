#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "sparsematrix.h"

int main (void)
{
	//Ï¡Êè¾ØÕóÔªËØ
	int A[5][5];
	int i, j, k;
	Mat matA;
	InitMat (&matA, 4, 3);
	for ( i = 1, k = 1; i < 5; i++ )
	{
		for ( j = 1; j < 4; j++, k++ )
		{
			A[i][j] = k;
			addElement (A[i][j], i, j, &matA);
		}
	}
	showMat (&matA);  
	removeElement (&matA, 4, 3);
	showMat (&matA);
	Mat matB;
	InitMat (&matB, 3, 4);
	for ( i = 1; i < 4; i++ )
	{
		for ( j = 1; j < 5; j++ )
		{
			if (i == j)
			{
				addElement (1, i, j, &matB);
			}
		}
	}
	showMat (&matB);
	Mat matAB;
	matAB = productMat (&matA, &matB);
	showMat (&matAB);
	getchar ();
	getchar ();
	return 0;
}