/* This file defines the struct of load flow data and 
   contains the variablze declarations and networks data */

#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

/*
 If there is a negative between i and j, it tells us
 a transformer in this branch and the Non-standard ratio is
 in negative end.
*/
typedef struct 	Branch_Type	   
{
	int i, j;	// i is headend node, j is end node
	char name_i[10], name_j[10];	// name of headend&end node
	double R, X, Y0, K;	
}Branch;

typedef struct Bus_type
{
	int seqNum, 
}Bus;

typedef struct Generator_Type
{
	double P, Q;	//P, Q is positive.
	int i;
	double V;
}Generator;

typedef struct Load_type
{
	double P, Q;	//P, Q is negative.
	int i;
	double V;
}Load;

typedef struct PVNode_Type
{
	double V;	//
	int i;
}PVNode;
#endif