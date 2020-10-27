#ifndef regras 
#define regras

#include <string>

using namespace std;

typedef enum Regras{
	PLINE0,
	P0,
	LDE0,
	LDE1,
	DE0,
	DE1,
	T0,
	T1,
	T2,
	T3,
	T4,
	DT0,
	DT1,
	DT2,
	DC0,
	DC1,
	DF0,
	LP0,
	LP1,
	B0,
	LDV0,
	LDV1,
	LS0,
	LS1,
	DV0,
	LI0,
	LI1,
	S0,
	S1,
	U0,
	U1,
	M0,
	M1,
	M2,
	M3,
	M4,
	M5,
	M6,
	E0,
	E1,
	E2,
	L0,
	L1,
	L2,
	L3,
	L4,
	L5,
	L6,
	R0,
	R1,
	R2,
	Y0,
	Y1,
	Y2,
	F0,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	LE0,
	LE1,
	LV0,
	LV1,
	LV2,
	IDD0,
	IDU0,
	ID0,
	TRUE0,
	FALSE0,
	CHR0,
	STR0,
	NUM0,
	NB0,
	MF0,
	MC0,
	NF0,
	MT0,
	ME0,
	MW0
} Regras;

class RegraOperator{

	public:
		RegraOperator();
		string getRegraString(Regras regra);
};


#endif