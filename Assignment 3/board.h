#pragma once

enum Colour {
	NONE = 0,
	YELLOW = 1,
	RED = 2
};

enum Move_result {
	MOVE_OK = 0,
	MOVE_OUT_OF_RANGE = 1,
	MOVE_COLUMN_FULL = 2,
	MOVE_WIN
};

class Board {
public:
	Board();
	Move_result insert_into_column(const int col, const Colour c);
	Colour get_colour_at_pos(const int x, const int y) const;
	void print() const;
	void remove_from_column(const int col);
	static const int NROWS = 6;
	static const int NCOLS = 7;
	static const int MAX_ENTRIES = NROWS*NCOLS;
private:
	int num_entries = 0;
	Colour grid[NROWS][NCOLS];
	int num_col_entries[NCOLS];
	void clear_old_printed_board() const;
	bool check_horizontal_win(const Colour c, const int row, const int col) const;
	bool check_vertical_win(const Colour c, const int row, const int col) const;
	bool check_diagonal_win(const Colour c) const;
	bool is_winning_move(const Colour c, const int row, const int col) const;
};
