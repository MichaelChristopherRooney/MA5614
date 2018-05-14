#pragma once

#include <vector>

class Point; // forward declaration

class Grid {
public:
	static const int GRID_SIZE = 5;
	Grid();
	void print() const;
	void update(int update_num);
	Point *get_point_at(int x, int y, int z);
private:
	void randomly_fill();
	std::vector<std::vector<std::vector<Point *> > > points; // 3D grid of points
};
