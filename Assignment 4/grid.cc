#include "grid.h"
#include "point.h"
#include "fishes.h"

#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

Grid::Grid() {
	points = vector<vector<vector<Point *> > >(GRID_SIZE,vector<vector<Point *> >(GRID_SIZE,vector <Point *>(GRID_SIZE)));
	randomly_fill();
}

// Randomly fills each point in the grid with either a random fish or nothing.
void Grid::randomly_fill() {
	random_device rd;
	mt19937 eng(rd()); 
	uniform_int_distribution<> distr(1, 10);
	for(int x = 0; x < GRID_SIZE; x++){
		for(int y = 0; y < GRID_SIZE; y++){
			for(int z = 0; z < GRID_SIZE; z++){
				points[x][y][z] = new Point(x, y, z, this);
				int num = distr(eng);
				if(num == 1){
					Tuna *t = new Tuna();
					points[x][y][z]->create_fish_here(TUNA, t);
					tunas.push_back(t);
				} else if(num == 2){
					Shark *s = new Shark();
					points[x][y][z]->create_fish_here(SHARK, s);
					sharks.push_back(s);
				} else if(num == 3){
					Minnow *m = new Minnow();
					points[x][y][z]->create_fish_here(MINNOW, m);
					minnows.push_back(m);
				} // else nothing at that particular point
			}
		}
	}
}

void Grid::print() const {
	for(int x = 0; x < GRID_SIZE; x++){
		for(int y = 0; y < GRID_SIZE; y++){
			for(int z = 0; z < GRID_SIZE; z++){
				Point *p = points[x][y][z];
				if(p->get_num_sharks() == 0 && p->get_num_tuna() == 0 && p->get_num_minnows() == 0){
					continue;
				}
				std::cout << "[" << x << "][" << y << "][" << z << "] contains: ";
				std::cout << p->get_num_sharks() << " sharks, " << p->get_num_tuna() << " tuna, " << p->get_num_minnows() << " minnows.\n";
			}
		}
	}
	std::cout << sharks.size() << " sharks\n";
	std::cout << tunas.size() << " tunas\n";
	std::cout << minnows.size() << " minnows\n";
}

Point *Grid::get_point_at(int x, int y, int z){
	return points[x][y][z];
}

int Grid::get_iteration_number() const {
	return iteration_number;
}

// A helper function that randomly selects a given fish from a vector.
int Grid::find_fish(std::vector<Fish *> *vec) const {
	if(vec->empty()){
		return -1;
	}
	return (rand() % vec->size());
}

// As per the assignment description a single species is chosen and a single 
// member of that species has a 90% chance to move.
// This is repeated L^3 times.
void Grid::update() {
	for(int i = 0; i < GRID_SIZE * GRID_SIZE * GRID_SIZE; i++){
		int will_move = ((rand() % 10) + 1) == 10 ? 0 : 1;
		if(!will_move){
			continue;
		}
		int species = (rand() % 3);
		int index;
		switch(species){
		case TUNA:
			index = find_fish((std::vector<Fish *> *)&tunas);
			if(index == -1){ // no fish in this species to move
				return;
			}
			tunas[index]->update(this);
			break;
		case SHARK:
			index = find_fish((std::vector<Fish *> *)&sharks);
			if(index == -1){ // no fish in this species to move
				return;
			}
			sharks[index]->update(this);
			break;
		case MINNOW:
			index = find_fish((std::vector<Fish *> *)&minnows);
			if(index == -1){ // no fish in this species to move
				return;
			}
			minnows[index]->update(this);	
			break;
		}
	}
	iteration_number++;
}

void Grid::add_minnow(Minnow *m){
	minnows.push_back(m);
}

void Grid::add_tuna(Tuna *t){
	tunas.push_back(t);
}

void Grid::add_shark(Shark *s){
	sharks.push_back(s);
}

// Given the vector of minnows at a point, remove each of these minnows from the 
// vector of all minnows in the grid.
void Grid::delete_all_minnows_from_point(std::vector<Minnow *> *vec){
	for(auto it = vec->begin(); it != vec->end(); it++){
		minnows.erase(std::remove(minnows.begin(), minnows.end(), *it), minnows.end());
	}
}

void Grid::delete_tuna(Tuna *t){
	tunas.erase(std::remove(tunas.begin(), tunas.end(), t), tunas.end());
}

// Applies periodic bounary conditions to the passed coordinate.
void Grid::adjust_coordinatate(int *c){
	if(*c == Grid::GRID_SIZE){
		*c = 0;
	} else if(*c == -1){
		*c = Grid::GRID_SIZE - 1;
	}
}

// Applies periodic boundary conditions to the passed coordinates
void Grid::apply_boundary(int *x, int *y, int *z){
	adjust_coordinatate(x);
	adjust_coordinatate(y);
	adjust_coordinatate(z);
}


