#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "parse-teste.h"
#include "next-token-test.h"

using namespace std;

int main(int argc, char** argv){

	printf("Starting testing of the lexical analyzer.\n");

	ParseTest parseTesting = ParseTest();
	// NextTokenTest nextTokenTest = NextTokenTest();


	parseTesting.run();
	// nextTokenTest.run();

	return 0;
}