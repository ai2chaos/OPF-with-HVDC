/************************************************************************/
/*This file defines the struct of load flow data and contains the 		*/
/*variablze declarations and NetWork Data                               */
/************************************************************************/

#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

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
	int i, j;	// i is headend node, j is end node
	int LFarea, LossZone;	//LFarea is not zero
	int Circuit, Type;
	float R, X, B;	
	int LineRate1, LineRate2, LineRate3;
	int CtrlBusNum, CtrlBusSide;
	float K, PhaseShifterDeg;
	float MinTap, MaxTap, StepSize, MinSorVol, MaxSorVol;
}Branch_Type;

typedef struct 
{
	/*
	Columns  1 - 4   Bus number (I) *
	Columns  7 - 17   Name (A) (left justify) *
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
	int BusNum;
	char Name[10];
	int LFarea, LossZone;	//LFarea is not zero
	int Type;
	float Vol, Deg, PL, QL, PG, QG, BaseVol, DesiredVol, MaxVol, MinVol;
	float ShuntG, ShuntB;
	int RemoteCtrlBus;
}Bus_Type;

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


#	ifdef _IEEE14_
#	endif

#	ifdef _TestCase_
#define Nbus 5
#define Nbranch 5
#define Ng 2
#define Nl 3
#define Npv 1
#	endif


#endif