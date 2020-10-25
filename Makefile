EXE=main
LEX_TEST=lexico/lexico-teste/
SIN_TEST=sintatico/sintatico-teste/

make: main.cpp
# 	g++ -c lexico/tokens.cpp -std=c++11  
# 	g++ -c main.cpp -std=c++11 
	g++ -o $(EXE) main.cpp -std=c++11  

run: make
	./$(EXE)

makeTestLex: $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp $(LEX_TEST)run-test.cpp
	g++ $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp $(LEX_TEST)run-test.cpp lexico/tokens.cpp lexico/lexico.cpp -std=c++11

runTestLex: makeTestLex
	./a.out

makeTestSin: $(SIN_TEST)sintatico-teste.cpp $(SIN_TEST)parse-teste.cpp $(SIN_TEST)run-tests.cpp
	g++ $(SIN_TEST)sintatico-teste.cpp $(SIN_TEST)parse-teste.cpp $(SIN_TEST)run-tests.cpp lexico/tokens.cpp lexico/lexico.cpp sintatico/sintatico.cpp naoTerminais/naoTerminais.cpp -std=c++11

runTestSin: makeTestSin
	./a.out