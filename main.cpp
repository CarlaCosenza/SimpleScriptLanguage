#include <stdio.h>

#include "lexico/tokens.cpp"

using namespace std;

int main(){

	Tokens token1 = searchKeyWord("array");
	Tokens token2 = searchKeyWord("carla");

	printf("encontrado: %d %d\n", token1, token2);
	printf("esperado %d %d\n", ARRAY, UNKNOWN);

	return 0;
}