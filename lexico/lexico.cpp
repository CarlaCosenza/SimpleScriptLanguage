#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "tokens.h"
#include "lexico.h"

using namespace std;

Lexico::Lexico(string program){
	this->constants.empty();
	this->identifiers.empty();
	this->programFileName = program;
	this->tokOps = TokensOperations();

	if(this->programFileName != "teste") {
		const char* programName = this->programFileName.c_str();
		this->pFile = fopen(programName, "w+");
	}
}

Lexico::~Lexico(){
	if(this->programFileName != "teste") fclose(this->pFile);
}

void Lexico::updateProgram(string program){
	if(this->programFileName != "teste") fclose(this->pFile);

	this->programFileName = program;
	if(this->programFileName != "teste") {
		const char* programName = this->programFileName.c_str();
		this->pFile = fopen(programName, "w+");
	}
}

int Lexico::addCharConstant(char c){
	Constant cons = {0, c, NULL, NULL};
	this->constants.push_back(cons);

	return this->constants.size() - 1;
}

int Lexico::addIntConstant(int n){
	Constant cons = {1, NULL, n, NULL};
	this->constants.push_back(cons);

	return this->constants.size() - 1;
}

int Lexico::addStringConstant(string s){
	Constant cons = {1, NULL, NULL, s};
	this->constants.push_back(cons);

	return this->constants.size() - 1;
}

char Lexico::getCharConstant(int n){
	char c = this->constants[n].cVal;

	return c;
}

int Lexico::getIntConstant(int n){
	int val = this->constants[n].nVal;

	return val;
}

string Lexico::getStringConstant(int n){
	string s = this->constants[n].sVal;

	return s;
}

char Lexico::readChar(){
	char c;
	fscanf(pFile, "%c", &c);

	return c;
}

bool Lexico::isAlpha(char c){
	if((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')) return true;
	return false;
}

bool Lexico::isDigit(char c){
	if(c >= '0' and c <= '9') return true;
	return false;
}

bool Lexico::isAlphaNumeric(char c){
	if(isAlpha(c) or isDigit(c)) return true;
	return false;
}

int Lexico::getNumber(string s){
	int numeral = 0;
	for(int i = 0 ; i < s.size() ; i++){
		int digit = s[i] - '0';
		numeral += numeral*10 + digit;
	}

	return numeral;
}

int Lexico::registerIdentifier(string s){
	int secondaryToken;
	if(this->identifiers.find(s) != this->identifiers.end()){
		secondaryToken = this->identifiers[s];
	} else {
		secondaryToken = this->identifiers.size();
		this->identifiers[s] = secondaryToken;
	}

	return secondaryToken;
}

Tokens Lexico::nextToken(void){
	char nextChar;
	Tokens token;
	int tokenSecundario;

	//loop do estado inicial para pular os separadores
	while(true){
		nextChar = readChar();
		if(nextChar != ' ' and nextChar != '\n') break;
	}

	if(isAlpha(nextChar)){
		string s = "";
		while(isAlphaNumeric(nextChar) or nextChar == '_'){
			s.push_back(nextChar);
			nextChar = readChar();
		}

		token = tokOps.searchKeyWord(s);
		if(token == UNKNOWN){
			// TO-DO: implement registerIdentifier
			this->registerIdentifier(s);
			token = ID;
		}

	} else if(isDigit(nextChar)){
		string s = "";
		while(isDigit(nextChar)){
			s.push_back(nextChar);
			nextChar = readChar();
		}

		token = NUMERAL;
		int numeral = getNumber(s);
		tokenSecundario = addIntConstant(numeral);

	} else if(nextChar == '"'){
		string s = "";
		s.push_back(nextChar);
		nextChar = readChar();
		while(nextChar != '"'){
			s.push_back(nextChar);
			nextChar = readChar();
		}
		s.push_back('"');

		token = STRING;
		tokenSecundario = addStringConstant(s);

	} else {
		switch(nextChar){
			case ':':
				token = COLON;
				break;
			case ';':
				token = SEMI_COLON;
				break;
			case ',':
				token = COMMA;
				break;
			case '*':
				token = TIMES;
				break;
			case '/':
				token = DIVIDE;
				break;
			case '.':
				token = DOT;
				break;
			case '[':
				token = LEFT_SQUARE;
				break;
			case ']':
				token = RIGHT_SQUARE;
				break;
			case '{':
				token = LEFT_BRACES;
				break;
			case '}':
				token = RIGHT_BRACES;
				break;
			case '(':
				token = LEFT_PARENTHESIS;
				break;
			case ')':
				token = RIGHT_PARENTHESIS;
				break;
			case '\'':
				nextChar = readChar();
				token = CHARACTER;
				tokenSecundario = addCharConstant
				(nextChar);
				nextChar = readChar(); // pular o ‘ 
				nextChar = readChar();
				break;
			case '&':
				nextChar = readChar();
				if(nextChar != '&'){
					printf("Caracter invalido.\n");
					break;
				}
				token = AND;
				break;
			case '|':
				nextChar = readChar();
				if(nextChar != '|'){
					printf("Caracter invalido.\n");
					break;
				}
				token = OR;
				break;
			case '=':
				nextChar = readChar();
				if(nextChar == '='){
					token = EQUAL_EQUAL;
				} else {
					token = EQUALS;
				}
				break;
			case '<':
				nextChar = readChar();
				if(nextChar == '='){
					token = LESS_OR_EQUAL;
				} else {
					token = LESS_THAN;
				}
				break;
			case '>':
				nextChar = readChar();
				if(nextChar == '='){
					token = GREATER_OR_EQUAL;
				} else {
					token = GREATER_THAN;
				}
				break;
			case '!':
				nextChar = readChar();
				if(nextChar == '='){
					token = NOT_EQUAL;
				} else {
					token = NOT;
				}
				break;
			case '+':
				nextChar = readChar();
				if(nextChar == '+'){
					token = PLUS_PLUS;
				} else {
					token = PLUS;
				}
				break;
			case '-':
				nextChar = readChar();
				if(nextChar == '-'){
					token = MINUS_MINUS;
				} else {
					token = MINUS;
				}
				break;
			default:
				token = UNKNOWN;
		}
	}

	// cout << "Found this token!" << this->tokOps.searchToken(token) << endl;

	return token;
}

vector<Tokens> Lexico::run(){
	vector<Tokens> tokenList;
	Tokens token = UNKNOWN;

	while(token != END_OF_FILE) {
		token = this->nextToken();
		tokenList.push_back(token);
	}

	return tokenList;
}