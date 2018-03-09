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

Colour Board::check_win_at_pos(const int row, const int col) const {
	//std::cout << "Checking row=" << row << ", col=" << col << "\n";
	Colour c = grid[row][col];
	bool win = false;
	// Check horizontal
	if(col >= 3){
		win = true;
		for(int i = col - 3; i <= col; i++){
			if(grid[row][i] != c){
				//std::cout << "Match failed at row " << row << " col " << i << "\n";
				win = false;
				break;
			}
		}
		if(win){
			return c;
		}
	}
	// Check vertical
	if(row >= 3){ // TODO: check this
		win = true;
		for(int i = row - 3; i <= row; i++){
			if(grid[i][col] != c){
				//std::cout << "Match failed at row " << i << " col " << col << "\n";
				win = false;
				break;
			}
		}
		if(win){
			return c;
		}
	}
	// TODO: diagonal
	return NONE;
}

Colour Board::check_win() const {
	for(int row = 0; row < NROWS; row++){
		for(int col = 0; col < NCOLS; col++){
			if(grid[row][col] != NONE){
				Colour c = check_win_at_pos(row, col);
				if(c != NONE){
					return c;
				}
			}		
		}
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
