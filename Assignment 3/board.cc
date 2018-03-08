#include "board.h"

#include <iostream>

Board::Board(){
	for(int i = 0; i < NROWS; i++){
		num_col_entries[i] = 0;
		for(int n = 0; n < NCOLS; n++){
			grid[i][n] = NONE;
		}
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
		return MOVE_COLUMN_FULL;
	}
	grid[(NROWS - 1 - num_entries)][col] = c;
	num_col_entries[col]++;
	return MOVE_OK;
}

// TODO: print in a nicer way.
// Use colours and clear the old grid.
void Board::print() const {
	std::cout << "=======================\n";
	for(int i = 0; i < NROWS; i++){
		for(int n = 0; n < NCOLS; n++){
			switch(grid[i][n]){
			case NONE:
				std::cout << "N, ";
				break;
			case YELLOW:
				std::cout << "Y, ";
				break;
			case RED:
				std::cout << "R, ";
				break;
			}
		}
		std::cout << "\n";
	}
}
