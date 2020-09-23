#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../tokens.h"
#include "../lexico.h"
#include "parse-teste.h"

using namespace std;

ParseTest::ParseTest(){}

void ParseTest::teste1(){
	printf("TEST #1\n");
	string text = "potato_\n";
	string parsedText = "";
	int i = 0;
	while(analisadorLexico.isAlphaNumeric(text[i]) or text[i] == '_'){
		parsedText.push_back(text[i]);
		i++;
	}
	cout << "Parsing the text " << text;
	cout << "Found " << parsedText << endl;

	return;

}

void ParseTest::teste2(){
	printf("TEST #2\n");
	string text = "potato_ &*$#!@";
	string parsedText = "";
	int i = 0;
	while(analisadorLexico.isAlphaNumeric(text[i]) or text[i] == '_'){
		parsedText.push_back(text[i]);
		i++;
	}
	cout << "Parsing the text " << text << endl;
	cout << "Found " << parsedText << endl;

	return;
}

void ParseTest::teste3(){
	printf("TEST #3\n");
	string text = "123849 @#41";
	string parsedText = "";
	int i = 0;
	while(analisadorLexico.isDigit(text[i])){
		parsedText.push_back(text[i]);
		i++;
	}
	cout << "Parsing the text " << text << endl;
	cout << "Found " << parsedText << endl;

	return;
}

void ParseTest::run(){
	printf("Running parsing tests...\n");
	teste1();
	teste2();
	teste3();
	printf("\n");

	return;
}
