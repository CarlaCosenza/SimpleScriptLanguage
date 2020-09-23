#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../lexico.h"
#include "next-token-test.h"

using namespace std;

NextTokenTest::NextTokenTest(){}

void NextTokenTest::teste1(){
	printf("TEST #1\n");
	string program = "lexico/lexico-teste/next-token-test1.txt";
	this->analisadorLexico.updateProgram(program);

	Tokens foundToken = this->analisadorLexico.nextToken();

	string foundTokenString = this->analisadorLexico.tokOps.searchToken(foundToken);
	string expectedTokenString = "ID";

	cout << "Found token " << foundTokenString << endl;
	cout << "Expected token " << expectedTokenString << endl;

	this->analisadorLexico.unread = false;

	return;
}

void NextTokenTest::teste2(){
	printf("TEST #2\n");
	string program = "lexico/lexico-teste/next-token-test2.txt";
	this->analisadorLexico.updateProgram(program);

	Tokens foundToken = this->analisadorLexico.nextToken();

	string foundTokenString = this->analisadorLexico.tokOps.searchToken(foundToken);
	string expectedTokenString = "ID";

	cout << "Found token " << foundTokenString << endl;
	cout << "Expected token " << expectedTokenString << endl;

	this->analisadorLexico.unread = false;

	return;
}

void NextTokenTest::teste3(){
	printf("TEST #3\n");
	string program = "lexico/lexico-teste/next-token-test3.txt";
	this->analisadorLexico.updateProgram(program);

	Tokens foundToken = this->analisadorLexico.nextToken();

	string foundTokenString = this->analisadorLexico.tokOps.searchToken(foundToken);
	string expectedTokenString = "NUMERAL";

	cout << "Found token " << foundTokenString << endl;
	cout << "Expected token " << expectedTokenString << endl;

	return;
}

void NextTokenTest::run(){
	printf("Running next token tests...\n");
	teste1();
	teste2();
	teste3();
	printf("\n");

	return;
}
