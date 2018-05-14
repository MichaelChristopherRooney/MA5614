#pragma once

#include <vector>

#include "fishes.h"

// Used an indicies into the event array
enum EVENT {
	NEW_MINNOWS = 0,
	NEW_TUNA = 1,
	NEW_SHARK = 2,
	TUNA_EAT_MINNOWS = 3,
	SHARK_EAT_TUNA = 4,
	SHARK_EAT_MINNOWS = 5
};

class Point {
public:
	Point(int x, int y, int z, Grid *g);
	void create_fish_here(enum FISH_TYPE type, Fish *f);
	void move_fish_to_here(enum FISH_TYPE type, Fish *f);
	void remove_fish(enum FISH_TYPE type, Fish *f);
	int get_num_sharks() const;
	int get_num_tuna() const;
	int get_num_minnows() const;
	int get_x_pos();
	int get_y_pos();
	int get_z_pos();

private:
	Point(); // disable default constructor
	int determine_events();
	enum EVENT pick_event() const;
	void handle_event(enum EVENT e);
	std::vector<Minnow *> minnows;
	std::vector<Tuna *> tunas;
	std::vector<Shark *> sharks;
	int x, y, z;
	static const int MAX_NUM_EVENTS = 6;
	int events[MAX_NUM_EVENTS]; // holds possible events when a fish arrives at the site
	Grid *grid;
};

