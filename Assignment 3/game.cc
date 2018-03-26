#include "board.h"
#include "player.h"

#include <iostream>
#include <unistd.h>

Player *p1;
Player *p2;
Player *cur;

enum Player_type read_player_type(){
	std::string line;
	std::getline(std::cin, line);
	if(line.length() != 1 || (line[0] != 'c' && line[0] != 'h')){
		std::cout << "Fatal error - bad input\n";
		exit(1);
	}
	if(line[0] == 'c'){
		return COMPUTER;
	} else {
		return HUMAN;
	}
}

void setup_game(){
	srand(time(NULL)); // for computer's random moves
	std::cout << "Is the red player human (h) or computer (c)?\n";
	enum Player_type t = read_player_type();
	p1 = new Player(t, RED);
	std::cout << "Is the yellow player human (h) or computer (c)?\n";
	t = read_player_type();
	p2 = new Player(t, YELLOW);
	cur = p1;
};

int main(void){
	setup_game();
	Board *b = new Board();;
	while(1){
		b->print();
		int result = cur->make_move(b);
		if(result == 1){ // returns 1 if the player won
			b->print();
			if(cur->get_colour() == YELLOW){
				std::cout << "Yellow won!\n";
			} else {
				std::cout << "Red won!\n";
			}
			return 0;
		}
		if(cur == p1){
			cur = p2;
		} else {
			cur = p1;
		}
	}
	return 0;
}
