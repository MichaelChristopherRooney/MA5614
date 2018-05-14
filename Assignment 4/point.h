#pragma once

#include <vector>

#include "fishes.h"

class Point {
public:
	Point(int x, int y, int z, Grid *g);
	void move_fish_to_here(enum FISH_TYPE type, Fish *f);
	
	int get_num_sharks() const;
	int get_num_tuna() const;
	int get_num_minnows() const;
	int get_x_pos();
	int get_y_pos();
	int get_z_pos();
	void update(int update_num);

private:
	Point(); // disable default constructor
	std::vector<Minnow *> minnows;
	std::vector<Tuna *> tunas;
	std::vector<Shark *> sharks;
	int x, y, z;
	Grid *grid;
};

