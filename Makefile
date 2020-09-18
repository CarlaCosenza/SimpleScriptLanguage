EXE=main

all: main.cpp
# 	g++ -c lexico/tokens.cpp -std=c++11  
# 	g++ -c main.cpp -std=c++11 
	g++ -o $(EXE) main.cpp -std=c++11  

run: all
	./$(EXE)