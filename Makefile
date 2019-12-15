# License GPL v3.0
# by Davide Fassio

all: Snake

Snake: main.cpp
	g++ main.cpp -lncurses -o Snake
	./Snake
	clear
