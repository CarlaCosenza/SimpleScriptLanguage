#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "parse-teste.h"
#include "next-token-test.h"
#include "run-test.h"

using namespace std;

int main(int argc, char** argv){

	printf("STARTING TESTING OF LEXICAL ANALYZER.\n \n");

	ParseTest parseTesting = ParseTest();
	NextTokenTest nextTokenTest = NextTokenTest();
	RunTest runTest = RunTest();

	parseTesting.run();
	nextTokenTest.run();
	runTest.run();

	return 0;
}