#pragma once

#include <vector>

#include "point.h"

class Grid {
public:
	static const int GRID_SIZE = 5;
	Grid();
	void print() const;
	void update();
private:
	void randomly_fill();
	void update_point(int x, int y, int z);
	std::vector<std::vector<std::vector<Point> > > points; // 3D grid of points
};
