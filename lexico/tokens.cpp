#include <stdio.h>
#include <map>
#include <string>

#include "tokens.h"

using namespace std;

map<string, Tokens> TokensOperations::reservedWordTokens = {
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

map<Tokens, string> TokensOperations::tokenNames = {
	{ARRAY, "Array"},
    {BOOLEAN,  "Boolean"},
	{BREAK,    "Break"},
	{CHAR,     "Char"},
	{CONTINUE, "Continue"},
	{DO,       "Do"},
	{ELSE,     "Else"},
	{FUNCTION, "Function"},
	{IF,       "If"},
	{INTEGER,  "Integer"},
	{OF,       "Of"},
	{STRING,   "String"},
	{STRUCT,   "Struct"},
	{TRUE,     "True"},
	{FALSE,    "False"},
	{TYPE,     "Type"},
	{VAR,      "Var"},
	{WHILE,    "While"},
	{COLON,            "Colon"},
	{SEMI_COLON,        "Semicolon"},
	{COMMA,            "Comma"},
	{EQUALS,           "Equals"},
	{LEFT_SQUARE,       "LeftSquare"},
	{RIGHT_SQUARE,      "RightSquare"},
	{LEFT_BRACES,       "LeftBraces"},
	{RIGHT_BRACES,      "RightBraces"},
	{LEFT_PARENTHESIS,  "LeftParenthesis"},
	{RIGHT_PARENTHESIS, "RightParenthesis"},
	{AND,              "And"},
	{OR,               "Or"},
	{LESS_THAN,         "LessThan"},
	{GREATER_THAN,      "GreaterThan"},
	{LESS_OR_EQUAL,      "LessOrEqual"},
	{GREATER_OR_EQUAL,   "GreaterOrEqual"},
	{NOT_EQUAL,         "NotEqual"},
	{EQUAL_EQUAL,       "EqualEqual"},
	{PLUS,             "Plus"},
	{PLUS_PLUS,         "PlusPlus"},
	{MINUS,            "Minus"},
	{MINUS_MINUS,       "MinusMinus"},
	{TIMES,            "Times"},
	{DIVIDE,           "Divide"},
	{DOT,              "Dot"},
	{NOT,              "Not"},
	{CHARACTER, "Character"},
	{NUMERAL,   "Numeral"},
	{STRINGVAL, "Stringval"},
	{ID,        "ID"},
	{UNKNOWN, "UNKNOWN"},
	{END_OF_FILE, "EOF"}
};

TokensOperations::TokensOperations(){}

string TokensOperations::searchToken(Tokens token){
	map<Tokens, string>::iterator it = tokenNames.find(token);
	if(it == tokenNames.end()) return "unknown";
	return it->second;
}

Tokens TokensOperations::searchKeyWord(string s){
	map<string, Tokens>::iterator it = reservedWordTokens.find(s);
	if(it == reservedWordTokens.end()) return UNKNOWN;
	return it->second;
}

