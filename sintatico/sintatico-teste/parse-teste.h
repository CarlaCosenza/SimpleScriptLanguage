#ifndef parsetestesintatico
#define parsetestesintatico

#include "../sintatico.h"

class ParseTesteSintatico{    

	public:
		Sintatico sin = Sintatico(NULL);

		ParseTesteSintatico(){};
		void shiftTeste(string s, int expected);
		void reduceTeste(string s, int expected);
		void testAll();
};


#endif