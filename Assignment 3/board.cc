#include "board.h"

#include <iostream>

#include <unistd.h>
#include <sys/types.h>

Board::Board(){
	for(int i = 0; i < NROWS; i++){
		for(int n = 0; n < NCOLS; n++){
			grid[i][n] = NONE;
		}
	}
	for(int i = 0; i < NCOLS; i++){
		num_col_entries[i] = 0;
	}
}

Colour Board::get_colour_at_pos(const int x, const int y) const {
	return grid[x][y];
}

// If the column is full returns 1
// If the index is out of range returns 2
// Otherwise returns 0.
// For each column we track how many tokens are in it already.
// We this to find the highest free index, which we take as the "bottom".
Move_result Board::insert_into_column(const int col, const Colour c){
	if(col > NCOLS || col < 0){
		return MOVE_OUT_OF_RANGE;
	}
	int num_entries = num_col_entries[col];
	if(num_entries == NROWS){
	std::cout << "3\n";
		return MOVE_COLUMN_FULL;
	}
	grid[(NROWS - 1 - num_entries)][col] = c;
	num_col_entries[col]++;
	return MOVE_OK;
}

// TODO: try get this working without using C functions
void Board::clear_old_printed_board() const{
	printf("\033[2J\033[1;1H");
}

// Note only need to check up to NCOLS - 3
Colour Board::check_horizontal_win() const {
	for(int i = 0; i < NROWS; i++){
		for(int j = 0; j < NCOLS - 3; j++){
			Colour c = grid[i][j];
			if(c == NONE){
				continue;
			}
			bool win = true;
			for(int n = 1; n < 4; n++){ // note n starts at 1
				if(grid[i][j + n] != c){
					win = false;
					break;
				}
			}
			if(win){
				return c;
			}
		}
	}
	return NONE;
}

// Note only need to check up to NROWS - 3
Colour Board::check_vertical_win() const {
	for(int j = 0; j < NCOLS; j++){
		for(int i = 0; i < NROWS - 3; i++){
			Colour c = grid[i][j];
			if(c == NONE){
				continue;
			}
			bool win = true;
			for(int n = 1; n < 4; n++){ // note n starts at 1
				if(grid[i + n][j] != c){
					win = false;
					break;
				}
			}
			if(win){
				return c;
			}
		}
	}
	return NONE;
}

Colour Board::check_diagonal_win() const {
	// TODO
	return NONE;
}

Colour Board::check_win() const {
	Colour c = check_horizontal_win();
	if(c != NONE){
		return c;
	}
	c = check_vertical_win();
	if(c != NONE){
		return c;
	}
	c = check_diagonal_win();
	if(c != NONE){
		return c;
	}
	return NONE;
}

void Board::print() const {
	clear_old_printed_board();
	for(int i = 0; i < NROWS; i++){
		for(int n = 0; n < NCOLS; n++){
			switch(grid[i][n]){
			case NONE:
				std::cout << "\033[1;40m  \033[0m  ";
				break;
			case YELLOW:
				std::cout << "\033[1;43m  \033[0m  ";
				break;
			case RED:
				std::cout << "\033[1;41m  \033[0m  ";
				break;
			}
		}
		std::cout << "\n\n";
	}
}
