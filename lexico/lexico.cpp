#include <stdio.h>
#include <string.h>
#include <vector.h>

#include "tokens.cpp"

typedef struct Constant {
	int type; // 0-char, 1-int, 2- string
	char cVal;
	int nVal;
	string sVal;
} Constant;

public class Lexico {

	public:

	vector<Constant> constants;
	string programFileName;
	FILE* pFile;

	Lexico(string program){
		constants.empty();
		programFileName = program;
		pFile = fopen(program, "w+");
	}

	~Lexico(){
		fclose (pFile);
	}

	int addCharConstant(char c){
		Constant cons = {0, c, NULL, NULL};
		this.constants.push_back(cons);

		return this.constants.size() - 1;
	}

	int addIntConstant(int n){
		Constant cons = {1, NULL, n, NULL};
		this.constants.push_back(cons);

		return this.constants.size() - 1;
	}

	int addStringConstant(string s){
		Constant cons = {1, NULL, NULL, s};
		this.constants.push_back(cons);

		return this.constants.size() - 1;
	}

	char getCharConstant(int n){
		char c = this.constants[n].cVal;

		return c;
	}

	int getIntConstant(int n){
		int val = this.constants[n].nVal;

		return val;
	}

	string getStringConstant(int n){
		string s = this.constants[n].sVal;

		return s;
	}

	char readChar(){
		char c;
		fscanf(pFile, "%c", &c);

		return c;
	}

	bool isAlpha(char c){
		if((c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z')) return true;
		return false;
	}

	bool isDigit(char c){
		if(c >= '0' and c <= '9') return true;
		return false;
	}

	bool isAlphaNumeric(char c){
		if(isAlpha(c) or isDigit(c)) return true;
		return false;
	}

	int getNumber(string s){
		int numeral = 0;
		for(int i = 0 ; i < s.size() ; i++){
			int digit = s[i] - '0';
			numeral += numeral*10 + digit;
		}

		return numeral;
	}

	Tokens nextToken(void){
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

			token = searchKeyWord(s);
			if(token == UNKNOWN){
				// TO-DO: implement registerIdentifier
				this.registerIdentifier(s);
				token = ID
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
			switch(nextChar):
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
					tokenSecundario = addCharConst(nectChar);
					nextChar = readChar(); // pular o ‘ 
					nextChar = readChar();
					break;
				default:
					token = UNKNOWN;
		}

		return token;
	}


}