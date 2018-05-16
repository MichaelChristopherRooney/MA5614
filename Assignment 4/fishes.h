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
	bool has_eaten = false;	
};

class Shark : public Fish {
public:
	void update(Grid *g);
	bool has_eaten = false;
};

class Minnow : public Fish {
public:
	void update(Grid *g);
};
