// License GPL v3.0
// by Davide Fassio

all: tui

tui: main.cpp
	g++ main.cpp -lncurses -o tui
	./tui
	clear
