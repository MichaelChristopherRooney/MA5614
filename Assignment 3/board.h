#pragma once

enum Colour {
	NONE,
	YELLOW,
	RED
};

enum Move_result {
	MOVE_OK = 0,
	MOVE_OUT_OF_RANGE = 1,
	MOVE_COLUMN_FULL = 2
};

class Board {
public:
	Board();
	Move_result insert_into_column(const int col, const Colour c);
	Colour get_colour_at_pos(const int x, const int y) const;
	void print() const;
	Colour check_win() const;
private:
	static const int NROWS = 6;
	static const int NCOLS = 7;
	Colour grid[NROWS][NCOLS];
	int num_col_entries[NCOLS];
	void clear_old_printed_board() const;
	Colour check_horizontal_win() const;
	Colour check_vertical_win() const;
	Colour check_diagonal_win() const;
};
