#include <stdio.h>
#include <iostream>

#include "parse-teste.h"

int main(){

	printf("Running full syntatical tests...\n");

	ParseTesteSintatico parseTest = ParseTesteSintatico();
	parseTest.testAll();

}