#ifndef runtestsintatico
#define runtest

using namespace std;

#include "../sintatico.h"
#include "../../lexico/lexico.h"

class RunTestSintatico {

	public:

		Lexico analisadorLexico = Lexico("teste");

		RunTestSintatico();
		void teste(string expected);
		void run();
};

#endif