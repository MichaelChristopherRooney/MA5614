#include <iostream>

#include "matrix.h"

Matrix::Matrix(int nrows, int ncols){
	this->nrows = nrows;
	this->ncols = ncols;
	this->data.assign(nrows, std::vector<double>(ncols, 0.0));
}

void Matrix::set(const int row, const int col, const double val){
	data[row][col] = val;
}

double Matrix::get(const int row, const int col){
	return data[row][col];
}

std::vector<double>& Matrix::operator[](const int row){
	return data[row];
}

double& Matrix::operator()(const int row, const int col){
	return data[row][col];
}

void Matrix::print(){
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < ncols; j++){
			std::cout << data[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

