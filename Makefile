EXE=main
LEX_TEST=lexico/lexico-teste/

make: main.cpp
# 	g++ -c lexico/tokens.cpp -std=c++11  
# 	g++ -c main.cpp -std=c++11 
	g++ -o $(EXE) main.cpp -std=c++11  

run: make
	./$(EXE)

makeTestLex: $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp $(LEX_TEST)run-test.cpp
	g++ $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp $(LEX_TEST)run-test.cpp lexico/tokens.cpp lexico/lexico.cpp -std=c++11

runTest: makeTestLex
	./a.out