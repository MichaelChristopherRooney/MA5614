#include "grid.h"

#include <iostream>
#include <random>

using namespace std;

Grid::Grid() {
	points = vector<vector<vector<Point> > >(GRID_SIZE,vector<vector<Point> >(GRID_SIZE,vector <Point>(GRID_SIZE)));
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
				int num = distr(eng);
				if(num == 1){
					Tuna *t = new Tuna();
					points[x][y][z].move_fish_to_here(TUNA, t);
				} else if(num == 2){
					Shark *s = new Shark();
					points[x][y][z].move_fish_to_here(SHARK, s);
				} else if(num == 3){
					Minnow *m = new Minnow();
					points[x][y][z].move_fish_to_here(MINNOW, m);
				} // else nothing at that particular point
			}
		}
	}
}

void Grid::print() const {
	for(int x = 0; x < GRID_SIZE; x++){
		for(int y = 0; y < GRID_SIZE; y++){
			for(int z = 0; z < GRID_SIZE; z++){
				Point p = points[x][y][z];
				std::cout << "[" << x << "][" << y << "][" << z << "] contains: ";
				std::cout << p.get_num_sharks() << " sharks, " << p.get_num_tuna() << " tuna, " << p.get_num_minnows() << " minnows.\n";
			}
		}
	}
}

void Grid::update() {
	for(int x = 0; x < GRID_SIZE; x++){
		for(int y = 0; y < GRID_SIZE; y++){
			for(int z = 0; z < GRID_SIZE; z++){
				update_point(x, y, z);
			}
		}
	}
}

// TODO
void Grid::update_point(int x, int y, int z){
	Point p = points[x][y][z];
	if(p.get_num_sharks() > 0){
		std::cout << "[" << x << "][" << y << "][" << z << "] move shark\n";
	}
	if(p.get_num_tuna() > 0){
		std::cout << "[" << x << "][" << y << "][" << z << "] move tuna\n";
	}
	if(p.get_num_minnows() > 0){
		std::cout << "[" << x << "][" << y << "][" << z << "] move minnow\n";
	}
}

