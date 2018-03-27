#include "player.h"

#include <chrono>
#include <iostream>
#include <thread>

Player::Player(enum Player_type type, enum Colour c){
	this->type = type;
	this->colour = c;
}

int Player::computer_find_immediate_winning_move(Board *b) const{
	for(int i = 0; i < b->NCOLS; i++){
		Move_result res = b->insert_into_column_for_computer_probing(i, this->colour);
		if(res == MOVE_WIN){
			b->remove_from_column_for_computer(i);
			b->insert_into_column(i, this->colour);
			return 1;
		} else if(res == MOVE_OK){
			b->remove_from_column_for_computer(i);
		}
	}
	return 0;
}

int Player::computer_try_block_opponent_winning_move(Board *b) const{
	enum Colour opp_colour;
	if(this->colour == RED){
		opp_colour = YELLOW;
	} else {
		opp_colour = RED;
	}
	for(int i = 0; i < b->NCOLS; i++){
		Move_result res = b->insert_into_column_for_computer_probing(i, opp_colour);
		if(res == MOVE_WIN){ // block the winning move
			b->remove_from_column_for_computer(i);
			b->insert_into_column(i, this->colour);
			return 1;
		} else if(res == MOVE_OK){
			b->remove_from_column_for_computer(i);
		}
	}
	return 0;
}

// One downside here is that it doesn't check if working towards the winning move
// could open up a winning move for the opponent.
int Player::computer_find_winning_two_moves(Board *b) const{
	for(int i = 0; i < b->NCOLS; i++){
		Move_result res = b->insert_into_column_for_computer_probing(i, this->colour);
		if(res != MOVE_OK){ // can't possibly win as we checked earlier
			continue;
		}
		for(int j = 0; j < b->NCOLS; j++){
			Move_result res = b->insert_into_column_for_computer_probing(j, this->colour);
			if(res == MOVE_WIN){ // work towards the winning move
				b->remove_from_column_for_computer(j);
				b->remove_from_column_for_computer(i);
				b->insert_into_column(i, this->colour);
				return 1;
			} else if(res == MOVE_OK){
				b->remove_from_column_for_computer(j);
			}
		}
		b->remove_from_column_for_computer(i);
	}
	return 0;
}

// See README.txt for details on the AI's rules.
// If no optimal action was taken 0 is returned.
// If a winning move is taken 1 is returned.
// If a non winning move is made (either to block an opponent's win or to
// work towards a win in two moves) then 2 is returned.
// If nothing is done here then a random move will be performed later.
int Player::computer_make_optimal_move(Board *b) const{
	// First check if a winning move can be made immediately	
	if(computer_find_immediate_winning_move(b) == 1){
		return 1;
	}
	// Next block any winning moves that can be made by the opponent
	if(computer_try_block_opponent_winning_move(b) == 1){
		return 2;
	}
	// Finally check if a winning move is at most two moves away try get there.
	if(computer_find_winning_two_moves(b)){
		return 2;
	}
	return 0;
}

// See README.txt for details on the AI's rules.
// Basically it first tries to make a smart move, and if it can't it just
// makes a random move.
int Player::computer_make_move(Board *b) const{
	if(this->colour == RED){
		std::cout << "Red computer is thinking...\n";
	} else {
		std::cout << "Yellow computer is thinking...\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
