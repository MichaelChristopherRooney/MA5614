#pragma once

#include <vector>

#include "fishes.h"

class Point {
public:
	void move_fish_to_here(enum FISH_TYPE type, Fish *f);
	int get_num_sharks() const;
	int get_num_tuna() const;
	int get_num_minnows() const;
private:
	std::vector<Shark *> sharks;
	std::vector<Tuna *> tunas;
	std::vector<Minnow *> minnows;
};

