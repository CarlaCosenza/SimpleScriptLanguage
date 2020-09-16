# EXE=main

all: lexico/tokens.cpp
	g++ lexico/tokens.cpp -std=c++11 -c     

run: all
# 	sudo ./$(EXE)