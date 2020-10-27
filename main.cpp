#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "lexico/tokens.h"
#include "lexico/lexico.h"
#include "sintatico/sintatico.h"

using namespace std;

string getProgramName(char* input){
	int n = strlen(input);
	string s = "";
	for(int i = 0 ; i < n ; i++){
		s.push_back(input[i]);
	}

	return s;
}

int main(int argc, char** argv){

	printf("Hello! Welcome to Carla and Karol's SSLang Compiler!\n");

	if(argc < 1) {
		printf("Please run the code with the name of the input code.\n");
		return 0;
	}

	string programName = getProgramName(argv[1]);

	Lexico analisadoLexico = Lexico(programName);
	Sintatico analisadorSintatico = Sintatico(&analisadoLexico);
	string result = analisadorSintatico.run();

	cout << result << endl;

	return 0;
}