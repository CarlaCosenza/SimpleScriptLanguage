#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "run-tests.h"

RunTestSintatico::RunTestSintatico(){}

void RunTestSintatico::teste(string expected){

	string result = this->analisadorSintatico.run(&(this->analisadorLexico));
	cout << "Found " << result << endl;
	cout << "Expected " << expected << endl;
}

void RunTestSintatico::run(){

	cout << "Running run tests" << endl;

	string fileName = "sintatico/sintatico-teste/runtest1.txt";
	this->analisadorLexico.updateProgram(fileName);
	cout << "Testing program " << fileName << endl;
	this->teste("success");

	fileName = "sintatico/sintatico-teste/runtest2.txt";
	this->analisadorLexico.updateProgram(fileName);
	cout << "Testing program " << fileName << endl;
	this->teste("Error at line 5");

	fileName = "sintatico/sintatico-teste/runtest3.txt";
	this->analisadorLexico.updateProgram(fileName);
	cout << "Testing program " << fileName << endl;
	this->teste("success");
}