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

// Reverts a previous play made by a computer play
// Computer can test if a play is a winner, then undo it with this.
void Board::remove_from_column(const int col){	
	if(col >= this->NCOLS || col < 0){
		return;
	}
	this->num_col_entries[col]--;
	this->num_entries--;
	int col_size = this->num_col_entries[col];
	this->grid[(NROWS - 1 - col_size)][col] = NONE;
}

// If the column is full returns MOVE_COLUMN_FULL
// If the index is out of range returns MOVE_OUT_OF_RANGE
// If winning move returns MOVE_WIN
// Otherwise returns MOVE_OK.
// For each column we track how many tokens are in it already.
// We this to find the highest free index, which we take as the "bottom".
// TODO: what if the board is full ?
Move_result Board::insert_into_column(const int col, const Colour c){
	if(this->num_entries == MAX_ENTRIES){
		printf("Board is full - tie game!\n");
		exit(1);
	}	
	if(col >= this->NCOLS || col < 0){
		return MOVE_OUT_OF_RANGE;
	}
	int col_size = num_col_entries[col];
	if(col_size == NROWS){
		return MOVE_COLUMN_FULL;
	}
	this->grid[(NROWS - 1 - col_size)][col] = c;
	this->num_col_entries[col]++;
	this->num_entries++;
	if(is_winning_move(c, this->NROWS - 1 - col_size, col)){
		return MOVE_WIN;
	}
	return MOVE_OK;
}

// TODO: try get this working without using C functions
void Board::clear_old_printed_board() const{
	printf("\033[2J\033[1;1H");
}

// In a horizontal win situation we check the entire row of the most recent
// insertion for 4 of the same colour in a row.
bool Board::check_horizontal_win(const Colour c, const int row, const int col) const {
	for(int i = 0; i < NCOLS; i++){
		int count  = 0;
		for(int n = i; grid[row][n] == c && n < NCOLS; n++){
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

// Unlike the other win checkers this does not use the most recent move's location.
// Basically take the top 3 rows and look for diagonal wins going down from these rows.
// Also don't bother checking for left diagonal wins if it's near the left edge, 
// and the same for the right edge.
bool Board::check_diagonal_win(const Colour c) const {
	for(int i = 0; i < 3; i++){ // note only first three rows
		for(int j = 0; j < NCOLS; j++){
			if(grid[i][j] != c){
				continue;
			}
			if(j < NCOLS - 3){ // check going down and right
				bool win = true;
				for(int n = 1; n < 4; n++){ // note n starts at 1
					if(grid[i + n][j + n] != c){
						win = false;
						break;
					}
				}
				if(win){
					return true;
				}
			}
			if(j >= 3){ // check going down and left
				bool win = true;
				for(int n = 1; n < 4; n++){ // note n starts at 1
					if(grid[i + n][j - n] != c){
						win = false;
						break;
					}
				}
				if(win){
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::is_winning_move(const Colour c, const int row, const int col) const {
	if(check_diagonal_win(c)){
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
