all: gameOfLife.cpp
	g++ gameOfLife.cpp -o gameOfLife -Wall -Werror -ggdb -funroll-loops -lncurses

clean :
	rm gameOfLife
