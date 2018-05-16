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
	void add_minnow(Minnow *m);
	void add_tuna(Tuna *t);
	void add_shark(Shark *s);
	int get_iteration_number() const;
	void delete_all_minnows_from_point(std::vector<Minnow *> *vec);
	void delete_tuna(Tuna *t);
	static void adjust_coordinatate(int *c);
	static void apply_boundary(int *x, int *y, int *z);
private:
	void randomly_fill();
	int select_random_fish	(std::vector<Fish *> *vec) const;
	std::vector<std::vector<std::vector<Point *> > > points; // 3D grid of points
	std::vector<Minnow *> minnows;
	std::vector<Tuna *> tunas;
	std::vector<Shark *> sharks;
	int iteration_number = 0;
};
