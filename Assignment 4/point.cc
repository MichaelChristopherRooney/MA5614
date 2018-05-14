#include "point.h"
#include "grid.h"

Point::Point(int x, int y, int z, Grid *g) {
	this->grid = g;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::update(int update_num){
	auto s_it = sharks.begin();
	while(s_it != sharks.end()){
		if((*s_it)->get_last_move() == update_num){ // already moved this turn
			s_it++;
		} else {
			(*s_it)->update(grid, update_num);
			s_it = sharks.erase(s_it);
		}

	}
	auto t_it = tunas.begin();
	while(t_it != tunas.end()){
		if((*t_it)->get_last_move() == update_num){ // already moved this turn
			t_it++; 
		} else {
			(*t_it)->update(grid, update_num);
			t_it = tunas.erase(t_it);
		}

	}
	auto m_it = minnows.begin();
	while(m_it != minnows.end()){
		if((*m_it)->get_last_move() == update_num){ // already moved this turn
			m_it++; 
		} else {
			(*m_it)->update(grid, update_num);
			m_it = minnows.erase(m_it);
		}
	}
}

void Point::move_fish_to_here(enum FISH_TYPE type, Fish *f) {
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

