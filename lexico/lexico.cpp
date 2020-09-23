#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "tokens.h"
#include "lexico.h"

using namespace std;

Constant::Constant(int type, char cVal, int nVal, string sVal){
	this->type = type;
	this->cVal = cVal;
	this->nVal = nVal;
	this->sVal = sVal;
}

Lexico::Lexico(string program){
	this->constants.empty();
	this->identifiers.empty();
	this->programFileName = program;
	this->tokOps = TokensOperations();
	this->unread = false;
	this->lastChar = ' ';

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
		this->pFile = fopen(programName, "r");
	}
}

int Lexico::addCharConstant(char c){
	Constant cons = Constant(0, c, -1, "");
	this->constants.push_back(cons);

	return this->constants.size() - 1;
}

int Lexico::addIntConstant(int n){
	Constant cons = Constant(1, '\0', n, "");
	this->constants.push_back(cons);

	return this->constants.size() - 1;
}

int Lexico::addStringConstant(string s){
	Constant cons = Constant(1, '\0', -1, s);
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
	if(this->unread){
		this->unread = false;
		c = this->lastChar;
	} else {
		if(fscanf(this->pFile, "%c", &c) == EOF) c = EOF;
	}

	return c;
}

void Lexico::unreadChar(char lastChar){
	this->unread = true;
	this->lastChar = lastChar;
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
		if(nextChar != ' ' and nextChar != '\n' and nextChar != '\t') break;
	}

	if(nextChar == EOF){
		token = END_OF_FILE;
	} else if(isAlpha(nextChar)){
		string s = "";
		while(isAlphaNumeric(nextChar) or nextChar == '_'){
			s.push_back(nextChar);
			nextChar = readChar();
		}

		token = tokOps.searchKeyWord(s);
		if(token == UNKNOWN){
			this->registerIdentifier(s);
			token = ID;
		}

		this->unreadChar(nextChar);

	} else if(isDigit(nextChar)){
		string s = "";
		while(isDigit(nextChar)){
			s.push_back(nextChar);
			nextChar = readChar();
		}

		token = NUMERAL;
		int numeral = getNumber(s);
		tokenSecundario = addIntConstant(numeral);

		this->unreadChar(nextChar);

	} else if(nextChar == '"'){
		string s = "";
		s.push_back(nextChar);
		nextChar = readChar();
		while(nextChar != '"'){
			s.push_back(nextChar);
			nextChar = readChar();
		}
		s.push_back('"');

		token = STRINGVAL;
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
					this->unreadChar(nextChar);
				}
				break;
			case '<':
				nextChar = readChar();
				if(nextChar == '='){
					token = LESS_OR_EQUAL;
				} else {
					token = LESS_THAN;
					this->unreadChar(nextChar);
				}
				break;
			case '>':
				nextChar = readChar();
				if(nextChar == '='){
					token = GREATER_OR_EQUAL;
				} else {
					token = GREATER_THAN;
					this->unreadChar(nextChar);
				}
				break;
			case '!':
				nextChar = readChar();
				if(nextChar == '='){
					token = NOT_EQUAL;
				} else {
					token = NOT;
					this->unreadChar(nextChar);
				}
				break;
			case '+':
				nextChar = readChar();
				if(nextChar == '+'){
					token = PLUS_PLUS;
				} else {
					token = PLUS;
					this->unreadChar(nextChar);
				}
				break;
			case '-':
				nextChar = readChar();
				if(nextChar == '-'){
					token = MINUS_MINUS;
				} else {
					token = MINUS;
					this->unreadChar(nextChar);
				}
				break;
			default:
				token = UNKNOWN;
		}
	}

	return token;
}

vector<Tokens> Lexico::run(){
	vector<Tokens> tokenList;
	Tokens token;

	while(token != END_OF_FILE) {
		token = this->nextToken();
		string tokenName = this->tokOps.searchToken(token);
		tokenList.push_back(token);
	}

	return tokenList;
}