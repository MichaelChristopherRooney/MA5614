#pragma once

#include "grid.h"

enum FISH_TYPE {
	TUNA,
	SHARK,
	MINNOW
};

class Fish {
public:
	virtual void update(Grid *g, int update_num) = 0;
	Point *get_point() const;
	void set_point(Point *p);
	int get_last_move() const;
	void set_last_move(int last_move);
private:
	Point *p;
	int last_move = -1;
};

class Tuna : public Fish {
public:
	void update(Grid *g, int update_num);
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Shark : public Fish {
public:
	void update(Grid *g, int update_num);
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Minnow : public Fish {
public:
	void update(Grid *g, int update_num);
};
