EXE=main
LEX_TEST=lexico/lexico-teste/

make: main.cpp
# 	g++ -c lexico/tokens.cpp -std=c++11  
# 	g++ -c main.cpp -std=c++11 
	g++ -o $(EXE) main.cpp -std=c++11  

run: make
	./$(EXE)

makeTest: $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp
	g++ $(LEX_TEST)lexico-test.cpp $(LEX_TEST)parse-teste.cpp $(LEX_TEST)next-token-test.cpp -std=c++11

runTest: makeTest
	./a.out