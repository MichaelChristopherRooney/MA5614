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

// Used for when the fish is leaving this point - NOT for when the fish is eaten
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

// Deletes all minnows at this point.
// Also ensures they are removed from the grid.
void Point::delete_minnows_here(){
	grid->delete_all_minnows_from_point(&minnows);
	for(auto it = minnows.begin(); it != minnows.end(); it++){
		free(*it);
	}
	minnows.clear();
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
	if(tunas.size() >= 2){
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
	if(sharks.size() >= 2){
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
		for(int i = 0; i < 3; i++){
			Minnow *m = new Minnow();
			create_fish_here(MINNOW, m);
			grid->add_minnow(m);
		}
		std::cout << "Spawning minnows\n";
		break;
	case NEW_TUNA: {
		Tuna *t = new Tuna();
		create_fish_here(TUNA, t);
		grid->add_tuna(t);
		std::cout << "Spawning tuna\n";
		break;
	}
	case NEW_SHARK:{
		Shark *s = new Shark();
		create_fish_here(SHARK, s);
		grid->add_shark(s);
		std::cout << "Spawning shark\n";
		break;
	}
	case TUNA_EAT_MINNOWS: // just pick the first tuna to be the one who eats
		std::cout << "Tuna eat minnows\n";
		(*tunas.begin())->has_eaten = true;
		delete_minnows_here();
		break;
	case SHARK_EAT_TUNA: { // just pick the first shark at this point to be the one who eats
		std::cout << "Shark eat Tuna\n";
		(*sharks.begin())->has_eaten = true;
		Tuna *t = *tunas.begin(); // delete the first tuna
		grid->delete_tuna(t);
		tunas.erase(std::remove(tunas.begin(), tunas.end(), t), tunas.end()); 
		free(t);
		break;
	}
	case SHARK_EAT_MINNOWS:
		std::cout << "Shark eat all minnows in neighbouring sites\n";
		(*sharks.begin())->has_eaten = true;
		int x, y, z;
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				for(int k = -1; k <= 1; k++){
					x = i + this->x, y = j + this->y, z = k + this->z;
					Grid::apply_boundary(&x, &y, &z);
					grid->get_point_at(x, y, z)->delete_minnows_here();
				}
			}
		}
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

