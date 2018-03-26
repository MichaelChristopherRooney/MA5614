#include "player.h"

#include <chrono>
#include <iostream>
#include <thread>

Player::Player(enum Player_type type, enum Colour c){
	this->type = type;
	this->colour = c;
}

// TODO: should have simple AI here
// Make it look for any available winning moves.
// Or any way to prevent the other player from getting a winning move
int Player::computer_make_move(Board& b) const{
	if(this->colour == RED){
		std::cout << "Red computer is thinking...\n";
	} else {
		std::cout << "Yellow computer is thinking...\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	Move_result res;
	do {
		int col = rand() % b.NCOLS;
		res = b.insert_into_column(col, this->colour);
		if(res == MOVE_WIN){
			return 1;
		}
	}while(res != MOVE_OK);
	return 0;
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
