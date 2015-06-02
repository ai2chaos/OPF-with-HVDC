/************************************************************************/
/*This file defines the struct of load flow data and contains the 		*/
/*variablze declarations and                                            */
/************************************************************************/
#include <stdio.h>
#include "sparsematrix.h"

/*定义潮流数据中需要的常数 */
//#define _TestCase_
#define _IEEE14_

#	ifdef _IEEE14_
//#define DataName "014ieee.DAT"
#define DataName "ieee14cdf.txt"
#define Nbus 14
#define Nbranch 20
#define Ng 5
#define NL 11
#define Npv 3
#	endif

#	ifdef _TestCase_
#define DataName "testcase.txt"
#define Nbus 5
#define Nbranch 5
#define Ng 2
#define NL 3
#define Npv 1
#	endif

/*定义数据结构*/
typedef struct 	
{
	/*
	Columns  1- 4   Tap bus number (I) *
	For transformers or phase shifters, the side of the model
	the non-unity tap is on
	Columns  6- 9   Z bus number (I) *
	For transformers and phase shifters, the side of the model
	the device impedance is on.
	Columns 11-12   Load flow area (I)
	Columns 13-14   Loss zone (I)
	Column  17      Circuit (I) * (Use 1 for single lines)
	Column  19      Type (I) *
	0 - Transmission line
	1 - Fixed tap
	2 - Variable tap for voltage control (TCUL, LTC)
	3 - Variable tap (turns ratio) for MVAR control
	4 - Variable phase angle for MW control (phase shifter)
	5 - DC Line直流传输线路 
	Columns 20-29   Branch resistance R, per unit (F) *
	Columns 30-40   Branch reactance X, per unit (F) * No zero impedance lines
	Columns 41-50   Line charging B, per unit (F) * (total line charging, +B)
	Columns 51-55   Line MVA rating No 1 (I) Left justify!
	Columns 57-61   Line MVA rating No 2 (I) Left justify!
	Columns 63-67   Line MVA rating No 3 (I) Left justify!
	Columns 69-72   Control bus number
	Column  74      Side (I)
	0 - Controlled bus is one of the terminals
	1 - Controlled bus is near the tap side
	2 - Controlled bus is near the impedance side (Z bus)
	Columns 77-82   Transformer final turns ratio (F)
	Columns 84-90   Transformer (phase shifter) final angle (F)
	Columns 91-97   Minimum tap or phase shift (F)
	Columns 98-104  Maximum tap or phase shift (F)
	Columns 106-111 Step size (F)
	Columns 113-119 Minimum voltage, MVAR or MW limit (F)
	Columns 120-126 Maximum voltage, MVAR or MW limit (F)
	*/
	int * i, * j;	// i is headend node, j is end node
	int * LFarea, * LossZone;	//LFarea is not zero
	int * Circuit, * Type;
	float * R, * X, * B;	
	int * LineRate1, * LineRate2, * LineRate3;
	int * CtrlBusNum, * CtrlBusSide;
	float * K, * PhaseShifterDeg;
	float * MinTap, * MaxTap, * StepSize, * MinSorVol, * MaxSorVol;
}Branch_Type;

typedef struct 
{
	/*
	Columns  1 - 4   Bus number (I) *
	Columns  6 - 17   Name (A) (left justify) *
	Columns 19 - 20   Load flow area number (I) Don't use zero! *
	Columns 21 - 23   Loss zone number (I)
	Columns 25 - 26   Type (I) *
	0 - Unregulated (load, PQ)
	1 - Hold MVAR generation within voltage limits, (PQ)
	2 - Hold voltage within VAR limits (gen, PV)
	3 - Hold voltage and angle (swing, V - Theta) (must always
	have one)
	Columns 28 - 33   Final voltage, p.u. (F)*
	Columns 34 - 40   Final angle, degrees (F) *
	Columns 41 - 49   Load MW (F) *
	Columns 50 - 59   Load MVAR (F) *				 
	Columns 60 - 67   Generation MW (F) *
	Columns 68 - 75   Generation MVAR (F) *
	Columns 77 - 83   Base KV (F)
	Columns 85 - 90   Desired volts (pu) (F)(This is desired remote voltage if
	this bus is controlling another bus.
	Columns 91 - 98   Maximum MVAR or voltage limit (F)
	Columns 99 - 106  Minimum MVAR or voltage limit (F)
	Columns 107 - 114 Shunt conductance G (per unit) (F)*
	Columns 115 - 122 Shunt susceptance B (per unit) (F)*
	Columns 124 - 127 Remote controlled bus number
	*/
	int * BusNum;
	char * Name;
	int * LFarea, * LossZone;	//LFarea is not zero
	int * Type;
	float * Vol, * Deg, * PL, * QL, * PG, * QG, * BaseVol, * DesiredVol, * MaxVol, * MinVol;
	float * ShuntG, * ShuntB;
	int * RemoteCtrlBus;
}Bus_Type;

typedef struct 
{
	double P, Q;	//P, Q is positive.
	int i;
	double V;
}Generator_Type;

typedef struct 
{
	double P, Q;	//P, Q is negative.
	int i;
	double V;
}Load_Type;

typedef struct 
{
	double V;	
	int i;
}PVNode_Type;

typedef struct 
{
	Bus_Type * BusData;		//指向Nbus个bus数据结构
	Branch_Type * BranchData;	//指向Nbranch个branch数据结构
}RawData_Type;
typedef struct
{
	Mat * A_Re;		//邻接矩阵
	Mat * A_Im;
	Mat * yb_Re;	//支路导纳矩阵
	Mat * yb_Im;
}AdjacencyMat_type;
typedef AdjacencyMat_type * AdjacencyMat;	//邻接矩阵指针

/*函数原型声明*/
void ImportData (RawData_Type * RawData);
void allocate_memory_rawdata (RawData_Type * RawData);
void allocate_memory_bus (Bus_Type * bus);
void allocate_memory_branch (Branch_Type * branch);
void initialize_RawData (RawData_Type * RawData, FILE * fptmp);
void initialize_BusData (Bus_Type * bus, char * Line);
void initialize_BranchData (Branch_Type * branch, char * Line);
AdjacencyMat CreatAdjacencyMatix (RawData_Type * RawData);
