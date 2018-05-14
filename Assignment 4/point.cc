#include "point.h"
#include "grid.h"

#include <random>
#include <iostream>
#include <algorithm>

Point::Point(int x, int y, int z, Grid *g) {
	this->grid = g;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::remove_fish(enum FISH_TYPE type, Fish *f){
	switch(type){
		case SHARK:
			sharks.erase(std::remove(sharks.begin(), sharks.end(), (Shark *)f), sharks.end());
			break;
		case TUNA:
			tunas.erase(std::remove(tunas.begin(), tunas.end(), (Tuna *)f), tunas.end());
			break;
		case MINNOW:
			minnows.erase(std::remove(minnows.begin(), minnows.end(), (Minnow *)f), minnows.end());
			break;
	}
}

// Used when intially spawning fish rather than them moving here
void Point::create_fish_here(enum FISH_TYPE type, Fish *f){
	f->set_point(this);
	switch(type){
		case SHARK:
			sharks.push_back((Shark *)f);
			break;
		case TUNA:
			tunas.push_back((Tuna *)f);
			break;
		case MINNOW:
			minnows.push_back((Minnow *)f);
			break;
	}
}

void Point::move_fish_to_here(enum FISH_TYPE type, Fish *f) {
	f->get_point()->remove_fish(type, f);
	f->set_point(this);
	switch(type){
		case SHARK:
			sharks.push_back((Shark *)f);
			break;
		case TUNA:
			tunas.push_back((Tuna *)f);
			break;
		case MINNOW:
			minnows.push_back((Minnow *)f);
			break;
	}
}

int Point::get_num_sharks() const {
	return sharks.size();
}

int Point::get_num_tuna() const {
	return tunas.size();
}

int Point::get_num_minnows() const {
	return minnows.size();
}

int Point::get_x_pos() {
	return x;
}

int Point::get_y_pos() {
	return y;
}

int Point::get_z_pos() {
	return z;
}

