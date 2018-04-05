#pragma once

#include <vector>

#include "point.h"

#include "shark.h"
#include "tuna.h"
#include "minnow.h"

class Grid {
private:
	std::vector<std::vector<std::vector<Point> > > points; // 3D grid of points
};
