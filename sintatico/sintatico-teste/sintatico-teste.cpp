#include <stdio.h>
#include <iostream>

#include "parse-teste.h"
#include "run-tests.h"

int main(){

	printf("Running full syntatical tests...\n");

	ParseTesteSintatico parseTest = ParseTesteSintatico();
	parseTest.testAll();

	RunTestSintatico runTest = RunTestSintatico();
	runTest.run();

	return 0;
}