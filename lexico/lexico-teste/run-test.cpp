#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../lexico.h"
#include "run-test.h"

using namespace std;

RunTest::RunTest(){}

void RunTest::printTokenVector(vector<Tokens> tokenList){
	cout << '{';
	for(int i = 0 ; i < tokenList.size() ; i++){
		string tokenName = this->analisadorLexico.tokOps.searchToken(tokenList[i]);
		cout << tokenName << ", ";
	}
	cout << '}' << endl;

	return;
}

void RunTest::teste1(){
	printf("TEST #1\n");
	string program = "lexico/lexico-teste/run-test1.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{ID, NUMERAL, ID, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::teste2(){
	printf("TEST #2\n");
	string program = "lexico/lexico-teste/run-test2.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{ID, STRINGVAL, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::teste3(){
	printf("TEST #3\n");
	string program = "lexico/lexico-teste/run-test3.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{VAR, ID, INTEGER, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::teste4(){
	printf("TEST #4\n");
	string program = "lexico/lexico-teste/run-test4.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{ID, EQUALS, CHARACTER, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::teste5(){
	printf("TEST 5\n");
	string program = "lexico/lexico-teste/run-test5.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES,
				LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL,
				GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES,
				DIVIDE, DOT, NOT, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::teste6(){
	printf("TEST #6\n");
	string program = "lexico/lexico-teste/run-test6.txt";
	this->analisadorLexico.updateProgram(program);

	vector<Tokens> foundTokens = this->analisadorLexico.run();

	vector<Tokens> expectedTokens{FUNCTION, ID, LEFT_PARENTHESIS, ID, COLON, INTEGER, RIGHT_PARENTHESIS, COLON, INTEGER, LEFT_BRACES, VAR, ID, COLON, INTEGER, SEMI_COLON, VAR, ID, COLON, INTEGER, SEMI_COLON, VAR, ID, COLON, INTEGER, SEMI_COLON, ID, EQUALS, NUMERAL, SEMI_COLON, ID, EQUALS, NUMERAL, SEMI_COLON, RIGHT_BRACES, END_OF_FILE};

	cout << "Found tokens: ";
	this->printTokenVector(foundTokens);
	cout << "Expected tokens: ";
	this->printTokenVector(expectedTokens);

	return;
}

void RunTest::run(){
	printf("Running full lexical tests...\n");
	teste1();
	teste2();
	teste3();
	teste4();
	teste5();
	teste6();
	printf("\n");

	return;
}
