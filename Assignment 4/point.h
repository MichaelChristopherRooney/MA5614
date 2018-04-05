#pragma once

#include <vector>

#include "shark.h"
#include "tuna.h"
#include "minnow.h"

class Point {
public:
	int get_num_sharks() const;
	int get_num_tuna() const;
	int get_num_minnows() const;
private:
	int num_sharks;
	int num_tuna;
	int num_minnows;
	std::vector<Shark> sharks;
	std::vector<Tuna> tuna;
	std::vector<Minnow> minnows;
};

