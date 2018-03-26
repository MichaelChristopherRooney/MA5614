#include "player.h"

#include <iostream> 

Player::Player(enum Player_type type, enum Colour c){
	this->type = type;
	this->colour = c;
}

int Player::computer_make_move(Board& b) const{
	std::cout << "TODO: computer player\n";
	// print out "computer is thinking..." or something like that
	return 1;
}

int Player::make_move(Board& b) const{
	if(this->type == COMPUTER){
		return computer_make_move(b);
	}
	if(this->colour == RED){
		std::cout << "Red player select a column:\n";
	} else {
		std::cout << "Yellow player select a column:\n";
	}
	Move_result res;
	do {
		int col;
		std::cin >> col;
		res = b.insert_into_column(col, this->colour);
		if(res == MOVE_OUT_OF_RANGE){
			std::cout << "Please enter a valid column number.\n";
		} else if(res == MOVE_COLUMN_FULL){
			std::cout << "Please select a non-full column.\n";
		} else if(res == MOVE_WIN){
			return 1;
		}
	}while(res != MOVE_OK);
	return 0;
}

enum Colour Player::get_colour() const{
	return this->colour;
}
