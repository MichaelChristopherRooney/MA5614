#include <iostream>

#include "matrix.h"

Matrix::Matrix(int nrows, int ncols){
	this->nrows = nrows;
	this->ncols = ncols;
	this->data.assign(nrows, std::vector<double>(ncols, 0.0));
}

void Matrix::print(){
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < ncols; j++){
			std::cout << data[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

