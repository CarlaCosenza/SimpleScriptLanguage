#ifndef tokens 
#define tokens

#include <map>

using namespace std;

typedef enum Tokens {

	//palavras reservadas
	INTEGER,
	CHAR,
	BOOLEAN,
	STRING,
	TYPE,
	EQUALS,
	ARRAY, 
	LEFT_SQUARE, 
	RIGHT_SQUARE, 
	OF,  
	STRUCT, 
	LEFT_BRACES, 
	RIGHT_BRACES, 
	SEMI_COLON, 
	COLON, 
	FUNCTION, 
	LEFT_PARENTHESIS, 
	RIGHT_PARENTHESIS, 
	COMMA,  
	VAR,
	IF, 
	ELSE, 
	WHILE,
	DO, 
	BREAK,  
 	CONTINUE, 
 	AND, 
	OR,
	LESS_THAN, 
	GREATER_THAN, 
	LESS_OR_EQUAL, 
	GREATER_OR_EQUAL, 
	EQUAL_EQUAL, 
	NOT_EQUAL, 
	PLUS,
	MINUS, 
	TIMES, 
	DIVIDE, 
	PLUS_PLUS, 
	MINUS_MINUS, 
	NOT,
	DOT, 
	ID,
	TRUE, 
	FALSE,   

	//Tokens regulares
	CHARACTER, 
	NUMERAL, 
	STRINGVAL, 

	//Token desconhecido
	UNKNOWN,

	//EOF
	END_OF_FILE,


} Tokens;

class TokensOperations{

	public:

		static map<string, Tokens> reservedWordTokens;
		static map<Tokens, string> tokenNames;

		TokensOperations();
		Tokens searchKeyWord(string s);
		string searchToken(Tokens token);
};


#endif