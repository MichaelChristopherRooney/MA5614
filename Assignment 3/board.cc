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
	if(col >= NCOLS || col < 0){
		return MOVE_OUT_OF_RANGE;
	}
	int num_entries = num_col_entries[col];
	if(num_entries == NROWS){
		return MOVE_COLUMN_FULL;
	}
	grid[(NROWS - 1 - num_entries)][col] = c;
	num_col_entries[col]++;
	if(is_winning_move(c, NROWS - 1 - num_entries, col)){
		return MOVE_WIN;
	}
	return MOVE_OK;
}

// TODO: try get this working without using C functions
void Board::clear_old_printed_board() const{
	//printf("\033[2J\033[1;1H");
}

// In a horizontal win situation we check the entire row of the most recent
// insertion for 4 of the same colour in a row.
bool Board::check_horizontal_win(const Colour c, const int row, const int col) const {
	for(int i = 0; i < NCOLS; i++){
		int count  = 0;
		for(int n = i; grid[row][n] == c && n - i < 4; n++){
			count++;
		}
		if(count == 4){
			return true;
		}
	}
	return false;
}

// In a vertical win situation we take the row and column of the most recent
// insertion and search for 3 matching colours below that position
bool Board::check_vertical_win(const Colour c, const int row, const int col) const {
	for(int n = 1; n < 4; n++){ // note n starts at 1
		if(grid[row + n][col] != c){
			return false;
		}
	}
	return true;
}

// TODO: fix this
bool Board::check_diagonal_win(const Colour c, const int row, const int col) const {
	return false;
}

bool Board::is_winning_move(const Colour c, const int row, const int col) const {
	if(check_diagonal_win(c, row, col)){
		return true;
	}
	if(check_vertical_win(c, row, col)){
		return true;
	}
	if(check_horizontal_win(c, row, col)){
		return true;
	}
	return false;
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
