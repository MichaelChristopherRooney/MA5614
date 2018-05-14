#pragma once

#include <vector>

// forward declarations
class Point;
class Fish;
class Minnow;
class Tuna;
class Shark;

class Grid {
public:
	static const int GRID_SIZE = 5;
	Grid();
	void print() const;
	void update();
	Point *get_point_at(int x, int y, int z);
private:
	void randomly_fill();
	int find_fish(std::vector<Fish *> *vec) const;
	std::vector<std::vector<std::vector<Point *> > > points; // 3D grid of points
	std::vector<Minnow *> minnows;
	std::vector<Tuna *> tunas;
	std::vector<Shark *> sharks;
};
