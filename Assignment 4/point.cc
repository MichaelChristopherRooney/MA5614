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

// This will modify the events array.
// Note it does not actually perform the event, just determines which are possible.
int Point::determine_events() {
	int num_events = 0;
	// Reset events array from last run
	for(int i = 0; i < MAX_NUM_EVENTS; i++){
		events[i] = 0;
	}
	// If at least two minnows then create three more minnows
	if(minnows.size() >= 2){ 
		events[NEW_MINNOWS] = 1;
		num_events++;
	}
	// If at least two tuna who have eaten then create one more tuna
	if(tunas.size() >= 2){ // TODO: check that they have eaten
		int count = 0;
		for(auto it = tunas.begin(); it != tunas.end(); it++){
			if((*it)->has_eaten){
				count++;
			}
		}
		if(count >= 2){
			events[NEW_TUNA] = 1;
			num_events++;
		}
	}
	// If at least two sharks who have eaten then create one more shark
	if(sharks.size() >= 2){ // TODO: check that they have eaten
		int count = 0;
		for(auto it = sharks.begin(); it != sharks.end(); it++){
			if((*it)->has_eaten){
				count++;
			}
		}
		if(count >= 2){
			events[NEW_SHARK] = 1;
			num_events++;
		}
	}
	// If at least one tuna and at least one minnow then delete all minnows at this point
	if(tunas.size() > 0 && minnows.size() > 0){
		events[TUNA_EAT_MINNOWS] = 1;
		num_events++;
	}
	// If at least one shark and at least one tuna then delete one tuna
	if(sharks.size() > 0 && tunas.size() > 0){
		events[SHARK_EAT_TUNA] = 1;
		num_events++;
	}
	// If at least one shark then delete all minnows at this point and the neighbouring points
	if(sharks.size() > 0){
		events[SHARK_EAT_MINNOWS] = 1;
		num_events++;
	}
	return num_events;
}

enum EVENT Point::pick_event() const {
	while(1){
		int index = rand() % MAX_NUM_EVENTS;
		if(events[index] == 1){
			return static_cast<enum EVENT>(index);
		}
	}
}

void Point::handle_event(enum EVENT e){
	switch(e){
	case NEW_MINNOWS:
/*
		for(int i = 0; i < 3; i++){
			Minnow *m = new Minnow();
			minnows.push_back(m);
			grid->add_minnow(m);
		}
		*/
		break;
	case NEW_TUNA:
		break;
	case NEW_SHARK:
		break;
	case TUNA_EAT_MINNOWS:
		break;
	case SHARK_EAT_TUNA:
		break;
	case SHARK_EAT_MINNOWS:
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
	int num_events = determine_events();
		std::cout << "Events: " << num_events << "\n";
	if(num_events > 0){
		enum EVENT e = pick_event();
		handle_event(e);
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

