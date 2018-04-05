#pragma once

class Fish {
public:
	int get_x_pos() const;
	int get_y_pos() const;
	int get_z_pos() const;
	virtual void make_move() = 0;
private:
	int x_pos;
	int y_pos;
	int z_pos;
};
