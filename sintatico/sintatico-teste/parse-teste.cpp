#include <stdio.h>
#include <iostream>

#include "parse-teste.h"

void ParseTesteSintatico::shiftTeste(string s, int expected){
	int result = this->sin.shift(s);
	cout << "Shifting the text " << s << endl;
	cout << "Found " << result << endl;
	cout << "Expected " << expected << endl;
}

void ParseTesteSintatico::reduceTeste(string s, int expected){
	int result = this->sin.reduce(s);
	cout << "Reducing the text " << s << endl;
	cout << "Found " << result << endl;
	cout << "Expected " << expected << endl;
}

void ParseTesteSintatico::testAll(){
	cout << "Running shift tests" << endl;
	this->shiftTeste("1324", -1);
	this->shiftTeste("s123", 123);
	this->shiftTeste("", -1);
	cout << endl;

	cout << "Running reduce tests" << endl;
	this->reduceTeste("1324", -1);
	this->reduceTeste("r123", 123);
	this->reduceTeste("", -1);
	cout << endl;
}