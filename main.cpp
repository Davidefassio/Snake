// License GPL v3.0
// by Davide Fassio

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define LEN 1000  // Max lenght of the snake

void print_map(int);
void opening();
void end(int);
void winend();

int main(int argc, char ** argv){
	srand(time(0));

	// Initialize the windows
	initscr();
	noecho();
	refresh();
	curs_set(0);
	halfdelay(1);

	// Main program
	int x, y, i, score = 0, act_len = 4;
	char move = 'w', prev_move = 'w';

	int food[2] = {rand()%49+1, rand()%23+1};
 	int snake[LEN][2];
	
	// Initialize the snake
	for(i = 0; i < act_len; i++){
		snake[i][0] = 25;
		snake[i][1] = 15 + i;
	}
	
	// Initialize the position with the head of the snake
	x = snake[0][0];
	y = snake[0][1];

	// Opening screen
	opening();
	
	// First print
	print_map(score);
	mvprintw(food[1], food[0], "@");
	mvprintw(snake[0][1], snake[0][0], "X");
	for(i = 1; i < act_len; i++){
		mvprintw(snake[i][1], snake[i][0], "O");	
	}
	
	// Game loop	
	while(1){
		// Wait 0.1s for an input
		if((move = getch()) == ERR){
			move = prev_move;
		}

		// In case of wrong key press
		m:

		switch(move){
			case 'w':
				prev_move = move;
				y--;
				break;

			case 'a':
				prev_move = move;
				x--;
				break;

			case 's':
				prev_move = move;
				y++;
				break;

			case 'd':
				prev_move = move;
				x++;
				break;
			default:
				// Wrong key press
				// Move like before
				move = prev_move;
				goto m;
				break;
		}
		// Food eaten
		if(food[0] == x && food[1] == y){
			score++;
			if(score >= 1000){
				// You win!
				winend();
				return 0;
			}

			while(1){	
				food[0] = rand()%49+1;
				food[1] = rand()%23+1;

				for(i = 0; i < act_len; i++){
					if(food[0] == snake[i][0] && food[1] == snake[i][1]){
						break;
					}
				}

				if(i == act_len){
					break;
				}
			}
			
			act_len++;
		}

		// Hit the borders
		if(x <= 0 || x > 50 || y <= 0 || y > 24){
			// You lose
			end(score);
			return 0;
		}

		// Update the snake
		for(i = act_len-1; i > 0; i--){
			// Move the snake forward
			snake[i][0] = snake[i-1][0];
			snake[i][1] = snake[i-1][1];
			
			// Collision withthe snake
			if(snake[i][0] == x && snake[i][1] == y){
				// You lose
				end(score);
				return 0;
			}
		}
		snake[0][0] = x;
		snake[0][1] = y;

		// Clear the screen
		clear();

		// Print the borders and score
		print_map(score);

		// Print the food
		mvprintw(food[1], food[0], "@");

		// Print the snake
		mvprintw(snake[0][1], snake[0][0], "X");
		for(i = 1; i < act_len; i++){
			mvprintw(snake[i][1], snake[i][0], "O");
		}

		// Update the window
		refresh();	
	}

	//Unexpected end
	return 0;
}

/* Print the border of the map, 
   the score and the escape key */
void print_map(int score){
	int i;

	mvprintw(0,  0, "############## Snake by Davide Fassio ##############");
	for(i = 1; i < 25; i++){
		mvprintw(i,  0, "#");
		mvprintw(i, 51, "#"); 
	}
	mvprintw(25, 0, "#################### Score:%4d #################### ", score);
}

// Opening screen
void opening(){
	mvprintw( 6, 6, "###### ##      ##   ####   ##   ## #######");
	mvprintw( 7, 6, "###### ####    ##  ##  ##  ##  ##  #######");
	mvprintw( 8, 6, "##     ## ##   ## ##    ## ## ##   ##     ");
	mvprintw( 9, 6, "###### ##  ##  ## ######## ####    ####   ");
	mvprintw(10, 6, "###### ##   ## ## ######## ####    ####   ");
	mvprintw(11, 6, "    ## ##    #### ##    ## ## ##   ##     ");
	mvprintw(12, 6, "###### ##     ### ##    ## ##  ##  #######");
	mvprintw(13, 6, "###### ##      ## ##    ## ##   ## #######");
	mvprintw(16, 15, "Press enter to start ...");
	refresh();

	while(getch() != 10){}
	clear();
}

// Ending screen
void end(int score){
	clear();
	mvprintw(10, 21, "Game over!");
	mvprintw(12, 17, "Your score is = %d", score);
	mvprintw(14, 14, "Press enter to leave ...");
	refresh();
	
	while(getch() != 10){}
	endwin();
}

// Win ending screen
void winend(){
	clear();
	mvprintw(10, 22, "You win!!");
	mvprintw(12, 16, "Your score is = 1000");
	mvprintw(14, 14, "Press enter to leave ...");
	refresh();

	while(getch() != 10){}
	endwin();
}

