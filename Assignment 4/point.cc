#include "point.h"

void Point::move_fish_to_here(enum FISH_TYPE type, Fish *f) {
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
