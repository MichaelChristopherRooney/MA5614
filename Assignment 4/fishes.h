#pragma once

#include "grid.h"

enum FISH_TYPE {
	TUNA = 0,
	SHARK = 1,
	MINNOW = 2
};

class Fish {
public:
	virtual void update(Grid *g) = 0;
	Point *get_point() const;
	void set_point(Point *p);
private:
	Point *p;
};

class Tuna : public Fish {
public:
	void update(Grid *g);
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Shark : public Fish {
public:
	void update(Grid *g);
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Minnow : public Fish {
public:
	void update(Grid *g);
};
