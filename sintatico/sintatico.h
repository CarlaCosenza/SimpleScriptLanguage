#ifndef sintatico 
#define sintatico

#include <vector>
#include <string>
#include <stack>

#include "../naoTerminais/naoTerminais.h"
#include "../lexico/lexico.h"
#include "../semantico/semantico.h"

using namespace std;

class Sintatico {

	public:

		static vector <vector <string> > actionTable;
		stack<int> stateStack;
		NaoTerminaisOperator naoTermOp;
		Lexico* analisadorLexico;
		Semantico analisadorSemantico;

		Sintatico(Lexico *lexico);
		string run();
		bool accept(string action);
		int shift(string action);
		int reduce(string action);
		int getNumberFromAction(string action);

};

#endif