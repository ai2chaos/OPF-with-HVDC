#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "sparsematrix.h"

int main (void)
{
	//ϡ�����Ԫ��
	int a11 = 1;
	int a12 = 2;
	int a13 = 3;
	int a14 = 4;
	int a21 = 5;
	int a22 = 6;
	int a23 = 7;
	int a24 = 8;
	int a33 = 5;
	int a42 = -2;
	int a44 = 6;

	Mat A;	//ָ��ϡ�����A��ָ�룬A��ֵΪϡ�����ĵ�ַ
	InitMat (&A);
	addElement (a11, 1, 1, &A);
	addElement (a12, 1, 2, &A);
	addElement (a13, 1, 3, &A);
	addElement (a21, 2, 1, &A);
	showMat (&A);
	getchar ();
	getchar ();
	return 0;
}