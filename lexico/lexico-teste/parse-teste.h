#ifndef parseTest
#define parseTest
using namespace std;

#include "../lexico.h"

class ParseTest {

	public:

		Lexico analisadorLexico = Lexico("teste");

		ParseTest();
		void teste1();
		void teste2();
		void teste3();
		void run();
};

#endif