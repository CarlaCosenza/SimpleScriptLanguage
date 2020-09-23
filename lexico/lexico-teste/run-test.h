#ifndef runtest
#define runtest
using namespace std;

#include "../lexico.h"

class RunTest {

	public:

		Lexico analisadorLexico = Lexico("teste");

		RunTest();
		void printTokenVector(vector<Tokens> tokens);
		void teste1();
		void teste2();
		void teste3();
		void teste4();
		void teste5();
		void teste6();
		void run();
};

#endif