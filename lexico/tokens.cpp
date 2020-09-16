#include <stdio.h>
#include <map>
#include <string>

using namespace std;

typedef enum Tokens {

	//palavras reservadas
	ARRAY, 
	BOOLEAN, 
	BREAK, 
	CHAR, 
	CONTINUE, 
	DO, 
	ELSE, 
	FALSE, 
	FUNCTION, 
	IF, 
	INTEGER, 
	OF, 
	STRING, 
	STRUCT, 
	TRUE, 
	TYPE, 
	VAR, 
	WHILE,

	//Simbolos
	COLON, 
	SEMI_COLON, 
	COMMA, 
	EQUALS, 
	LEFT_SQUARE, 
	RIGHT_SQUARE, 
	LEFT_BRACES, 
	RIGHT_BRACES, 
	LEFT_PARENTHESIS, 
	RIGHT_PARENTHESIS, 
	AND, 
	OR, 
	LESS_THAN, 
	GREATER_THAN, 
	LESS_OR_EQUAL, 
	GREATER_OR_EQUAL, 
	NOT_EQUAL, 
	EQUAL_EQUAL, 
	PLUS, 
	PLUS_PLUS, 
	MINUS, 
	MINUS_MINUS, 
	TIMES, 
	DIVIDE, 
	DOT, 
	NOT,

	//Tokens regulares
	CHARACTER, 
	NUMERAL, 
	STRINGVAL, 
	ID,

	//Token desconhecido
	UNKNOWN


} Tokens;

map<string, Tokens> reservedWordTokens = {
	{"array", ARRAY}, 
	{"boolean", BOOLEAN}, 
	{"break", BREAK}, 
	{"char", CHAR}, 
	{"continue", CONTINUE}, 
	{"do", DO}, 
	{"else", ELSE}, 
	{"false", FALSE}, 
	{"function", FUNCTION}, 
	{"if", IF}, 
	{"integer", INTEGER}, 
	{"of", OF}, 
	{"string", STRING}, 
	{"struct", STRUCT}, 
	{"true", TRUE}, 
	{"type", TYPE}, 
	{"var", VAR}, 
	{"while", WHILE}
};
