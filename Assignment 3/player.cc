#include "player.h"

#include <chrono>
#include <iostream>
#include <thread>

Player::Player(enum Player_type type, enum Colour c){
	this->type = type;
	this->colour = c;
}

// This will look for any winning moves and make them.
// If it fails to find any winning moves for its own colourc it will check
// if it can block the opposing player from making a winning move.
// If no optimal action was taken 0 is returned.
// If a winning move is taken 1 is returned.
// If an opponent's winning move is blocked 2 is returned.
// If nothing is done here then a random move will be performed.
int Player::computer_make_optimal_move(Board *b) const{
	for(int i = 0; i < b->NCOLS; i++){
		Move_result res = b->insert_into_column(i, this->colour);
		if(res == MOVE_WIN){
			return 1;
		} else if(res == MOVE_OK){
			b->remove_from_column(i);
		}
	}
	enum Colour opp_colour;
	if(this->colour == RED){
		opp_colour = YELLOW;
	} else {
		opp_colour = RED;
	}
	for(int i = 0; i < b->NCOLS; i++){
		Move_result res = b->insert_into_column(i, opp_colour);
		if(res == MOVE_WIN){ // block the winning move
			b->remove_from_column(i);
			b->insert_into_column(i, this->colour);
			return 2;
		} else if(res == MOVE_OK){
			b->remove_from_column(i);
		}
	}
	return 0;
}

// The computer first tries to make a winning move.
// If no winning move can be made it will block the other player from making
// a winning move if one is available to them.
// Otherwise it makes a random move.
int Player::computer_make_move(Board *b) const{
	if(this->colour == RED){
		std::cout << "Red computer is thinking...\n";
	} else {
		std::cout << "Yellow computer is thinking...\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	int result = computer_make_optimal_move(b);
	if(result == 1){
		return 1;
	} else if(result == 2){
		return 0;
	}
	Move_result res;
	do {
		int col = rand() % b->NCOLS;
		res = b->insert_into_column(col, this->colour);
		if(res == MOVE_WIN){
			return 1;
		}
	}while(res != MOVE_OK);
	return 0;
}

int Player::make_move(Board *b) const{
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
		res = b->insert_into_column(col, this->colour);
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
