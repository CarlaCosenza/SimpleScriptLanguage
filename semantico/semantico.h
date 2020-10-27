#ifndef semantico 
#define semantico

#include <stack>

#include "../escopo/escopo.h"
#include "../lexico/lexico.h"
#include "../naoTerminais/naoTerminais.h"

typedef struct {
  NaoTerminais type;
  int nSize;
  union {
    struct {
      PObject obj;
      int name;
    } ID;

    struct {
      PObject type;
    } T,E,L,R,Y,F,LV;

    struct {
        PObject type;
        PObject param;
        int err;
    } MC;

    struct {
        int label;
    } MT,ME,MW,MA;

    struct{
        PObject type;
        PObject param;
        int err;
        int n;
    } LE;

    struct {
        PObject list;
    } LI,DC,LP;

    struct {
        PObject type;
        int val;
    } TRU,FALS;

    struct {
        PObject type;
        int pos;
        char val;
    } CHR;

    struct {
        PObject type;
        char* val;
        int pos;
    } STR;

    struct {
        PObject type;
        int val;
        int pos;
    } NUM;
  };
} t_attrib;

class Semantico{

	public:
		FILE *out;
		PObject curFunction;
		Lexico* analisadorLexico;
		int functionVarPos;
		int nFuncs;

		stack <t_attrib> semanticoStack;

		Semantico(Lexico* analisadorLexico);
		Semantico(){};
		~Semantico();
		int new_label();
		void parseRule(int rule);
		
};


#endif