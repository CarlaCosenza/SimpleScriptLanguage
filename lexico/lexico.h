#ifndef lexico 
#define lexico

#include <map>

#include "tokens.h"

using namespace std;

class Constant {
	public:
		int type; // 0-char, 1-int, 2- string
		char cVal;
		int nVal;
		string sVal;

		Constant(int type, char cVal, int nVal, string sVal);
};

class Lexico {

	public:

		vector<Constant> constants;
		string programFileName;
		FILE* pFile;
		map <string, int> identifiers;
		TokensOperations tokOps;
		bool unread;
		char lastChar;

		Lexico(string program);
		~Lexico();
		void updateProgram(string program);
		int addCharConstant(char c);
		int addIntConstant(int n);
		int addStringConstant(string s);
		char getCharConstant(int n);
		int getIntConstant(int n);
		string getStringConstant(int n);
		char readChar();
		void unreadChar(char lastChar);
		bool isAlpha(char c);
		bool isDigit(char c);
		bool isAlphaNumeric(char c);
		int getNumber(string s);
		int registerIdentifier(string s);
		Tokens nextToken(void);
		vector<Tokens> run();
};

#endif