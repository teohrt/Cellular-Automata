all: main.cpp
	g++ gameOfLife.cpp main.cpp wolfram.cpp -o automata -Wall -Werror -ggdb -funroll-loops -lncurses

clean :
	rm automata
