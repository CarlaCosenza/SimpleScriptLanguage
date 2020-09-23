#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../lexico.h"
#include "next-token-test.h"

using namespace std;

NextTokenTest::NextTokenTest(){}

void NextTokenTest::teste1(){
	string program = "next-token-test1.txt";
	// this->analisadorLexico.updateProgram(program);

	// Tokens foundToken = this->analisadorLexico.nextToken();

	string foundTokenString = "carla";
	string expectedTokenString = "ID";

	cout << "Found token " << foundTokenString;
	cout << "Expected token " << expectedTokenString << endl << endl;

	return;

}

void NextTokenTest::run(){
	teste1();

	return;
}
