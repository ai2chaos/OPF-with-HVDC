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
	InitMat (&matA);
	for ( i = 4, k = 1; i > 0; i-- )
	{
		for ( j = 4; j > 0; j--, k++ )
		{
			A[i][j] = k;
			addElement (A[i][j], i, j, &matA);
		}
	}
	showMat (&matA);  
	addElement (100, 3, 4, &matA);
	showMat (&matA);
	//removeElement (&matA, 6, 2);
	showMat (&matA);
	addElement (100, 2, 2, &matA);
	//removeElement (&matA, 2, 4);
	//removeElement (&matA, 3, 4);
	//removeElement (&matA, 4, 4);
	showMat (&matA);
	getchar ();
	getchar ();
	return 0;
}