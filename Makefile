all: tui

tui: main.cpp
	g++ main.cpp -lncurses -o tui
	./tui
	clear
