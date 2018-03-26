#pragma once

#include "board.h"

enum Player_type {
	HUMAN,
	COMPUTER
};

class Player {
public:
	Player(enum Player_type type, enum Colour c);
	int make_move(Board& b) const;
	enum Colour get_colour() const;
	
private:
	Player(); // disable default
	int computer_make_move(Board& b) const;
	enum Player_type type;
	enum Colour colour;
};
