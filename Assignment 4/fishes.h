#pragma once

enum FISH_TYPE {
	TUNA,
	SHARK,
	MINNOW
};

class Fish {
public:
	int get_x_pos() const;
	int get_y_pos() const;
	int get_z_pos() const;
	virtual void update() = 0;
private:
	int x_pos;
	int y_pos;
	int z_pos;
};

class Tuna : public Fish {
public:
	void update();
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Shark : public Fish {
public:
	void update();
private:
	bool has_eaten = false;
	int last_eaten = -1; // number of the iteration when it last ate
};

class Minnow : public Fish {
public:
	void update();
};
