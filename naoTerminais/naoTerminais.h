#ifndef naoterminais 
#define naoterminais

#include "../lexico/tokens.h"

typedef enum NaoTerminais {
	PLINE = END_OF_FILE + 1,
	P,
	LDE,
	DE,
	T,
	DT,
	DC,
	DF,
	LP,
	B,
	LDV,
	LS,
	DV,
	LI,
	S,
	U,
	M,
	E,
	L,
	R,
	Y,
	F,
	LE,
	LV,
	IDD,
	IDU,
	ID1,
	TRUE1,
	FALSE1,
	CHR,
	STR,
	NUM,
	NB,
	MF,
	MC,
	NF,
	MT,
	ME,
	MW

} NaoTerminais;


class NaoTerminaisOperator{

	public:
		static vector <NaoTerminais> ruleLeftTokens;
		static vector <int> ruleNumberOfTokens;
};


#endif