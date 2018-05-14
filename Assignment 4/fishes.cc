#include "fishes.h"
#include "point.h"
#include "grid.h"

#include "stdio.h"
#include <random>

enum AXIS {
	X_AXIS = 0,
	Y_AXIS = 1,
	Z_AXIS = 2
};

//////////////////////////////////////////////////////
// General fish functions
//////////////////////////////////////////////////////

void Fish::set_point(Point *p) {
	this->p = p;
}

Point *Fish::get_point() const {
	return p;
}

void Fish::set_last_move(int last_move){
	this->last_move = last_move;
}

int Fish::get_last_move() const {
	return last_move;
}	

//////////////////////////////////////////////////////
// Tuna functions
//////////////////////////////////////////////////////

// Moves diagonally 
// First randomly move up or down (y-axis)
// Then move randomly up or down in either the x or z axis
void Tuna::update(Grid *g, int update_num) {
	set_last_move(update_num);
	int pos[3]; // xyz
	pos[X_AXIS] = get_point()->get_x_pos();
	pos[Y_AXIS] = get_point()->get_y_pos() + ((rand() % 2) == 0 ? -1 : 1); // move up or down 1 block in y axis
	pos[Z_AXIS] = get_point()->get_z_pos();
	if(pos[Y_AXIS] == g->GRID_SIZE){
		pos[Y_AXIS] = 0;
	} else if(pos[Y_AXIS] == -1){
		pos[Y_AXIS] = 4;
	}
	int axis = Y_AXIS;
	while(axis == Y_AXIS){ // randomly pick from the x or z axis
		axis = rand() % 3;
	}
	pos[axis] = pos[axis] + ((rand() % 2) == 0 ? -1 : 1);	
	if(pos[axis] == g->GRID_SIZE){
		pos[axis] = 0;
	} else if(pos[axis] == -1){
		pos[axis] = 4;
	}
	printf("Tuna moved to [%d][%d][%d] from [%d][%d][%d]\n",
		pos[0], pos[1], pos[2], get_point()->get_x_pos(), get_point()->get_y_pos(), get_point()->get_z_pos()
	);
	g->get_point_at(pos[0], pos[1], pos[2])->move_fish_to_here(TUNA, this);
	
}

//////////////////////////////////////////////////////
// Shark functions
//////////////////////////////////////////////////////

void Shark::update(Grid *g, int update_num){
	set_last_move(update_num);
	int pos[3]; // xyz
	pos[X_AXIS] = get_point()->get_x_pos();
	pos[Y_AXIS] = get_point()->get_y_pos();
	pos[Z_AXIS] = get_point()->get_z_pos();
	int axis_1 = rand() % 3; // axis with two moves
	int axis_2 = axis_1; // axis with one move
	int direction_1 = rand() % 2; // 0 for backwards, 1 for forwards
	int direction_2 = rand() % 2;
	while(axis_2 == axis_1){ // ensure it's different from first axis
		axis_2 = rand() % 3;
	}
	if(pos[axis_1] == g->GRID_SIZE - 2 && direction_1 == 1){
		pos[axis_1] = 0;
	} else if(pos[axis_1] == g->GRID_SIZE - 1 && direction_1 == 1){
		pos[axis_1] = 1;
	} else if(pos[axis_1] == 0 && direction_1 == 0){
		pos[axis_1] = 3;
	} else if(pos[axis_1] == 1 && direction_1 == 0){
		pos[axis_1] = 2;
	} else {
		pos[axis_1] = pos[axis_1] + (direction_1 == 0 ? -2 : 2);
	}
	pos[axis_2] = pos[axis_2] + (direction_2 == 0 ? -1 : 1);
	if(pos[axis_2] == g->GRID_SIZE){
		pos[axis_2] = 0;
	} else if(pos[axis_2] == -1){
		pos[axis_2] = 4;
	}
	printf("Shark moved to [%d][%d][%d] from [%d][%d][%d]\n",
		pos[0], pos[1], pos[2], get_point()->get_x_pos(), get_point()->get_y_pos(), get_point()->get_z_pos()
	);
	g->get_point_at(pos[0], pos[1], pos[2])->move_fish_to_here(SHARK, this);
}

//////////////////////////////////////////////////////
// Minnow functions
//////////////////////////////////////////////////////

// Can move to any neighbouring site.
// First pick an axis, then a direction.
// If new position is invalid we need to apply periodic boundary conditions.
void Minnow::update(Grid *g, int update_num) {
	set_last_move(update_num);
	int pos[3]; // xyz
	pos[0] = get_point()->get_x_pos();
	pos[1] = get_point()->get_y_pos();
	pos[2] = get_point()->get_z_pos();
	int axis = rand() % 3;
	int direction = rand() % 2;
	pos[axis] = pos[axis] + (direction == 1 ? 1 : -1);
	if(pos[axis] == g->GRID_SIZE){
		pos[axis] = 0;
	} else if(pos[axis] == -1){
		pos[axis] = 4;
	}
	printf("Minnow moved to [%d][%d][%d] from [%d][%d][%d]\n",
		pos[0], pos[1], pos[2], get_point()->get_x_pos(), get_point()->get_y_pos(), get_point()->get_z_pos()
	);
	g->get_point_at(pos[0], pos[1], pos[2])->move_fish_to_here(MINNOW, this);
}
