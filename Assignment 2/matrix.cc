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

double Matrix::get(const int row, const int col) const{
	return data[row][col];
}

std::vector<double>& Matrix::operator[](const int row){
	return data[row];
}

std::vector<double> Matrix::operator[](const int row) const{
	return data[row];
}

double& Matrix::operator()(const int row, const int col){
	return data[row][col];
}

Matrix& Matrix::operator=(const Matrix& m){
	this->nrows = m.nrows;
	this->ncols = m.ncols;
	this->data = m.data;
	return *this;
}

Matrix Matrix::operator+(const Matrix& other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		// TODO: some kind of error here
	}
	Matrix n(this->nrows, this->ncols);
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			n[i][j] = this->data[i][j] + other[i][j];
		}
	}
	return n;
}

void Matrix::operator+=(const Matrix& other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		// TODO: some kind of error here
	}
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			this->data[i][j] = this->data[i][j] + other[i][j];
		}
	}
}

Matrix Matrix::operator-(const Matrix& other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		// TODO: some kind of error here
	}
	Matrix n(this->nrows, this->ncols);
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			n[i][j] = this->data[i][j] - other[i][j];
		}
	}
	return n;
}

void Matrix::operator-=(const Matrix& other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		// TODO: some kind of error here
	}
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			this->data[i][j] = this->data[i][j] - other[i][j];
		}
	}
}

Matrix Matrix::operator*(const Matrix& other){
	if(this->ncols != other.nrows){
		// TODO: some kind of error here
	}
	Matrix n(this->nrows, other.ncols);
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < other.ncols; j++){
			double sum = 0.0;
			for(int k = 0; k < this->ncols; k++){
				sum += this->data[i][k] * other[k][j];
			}
			n[i][j] = sum;
		}
	}
	return n;
}

void Matrix::operator*=(const Matrix& other){
	if(this->ncols != other.nrows){
		// TODO: some kind of error here
	}
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < other.ncols; j++){
			double sum = 0.0;
			for(int k = 0; k < this->ncols; k++){
				sum += this->data[i][k] * other[k][j];
			}
			this->data[i][j] = sum;
		}
	}
}

bool Matrix::operator==(const Matrix &other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		return false;
	}
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			if(this->data[i][j] != other[i][j]){
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix &other){
	if(this->nrows != other.nrows || this->ncols != other.ncols){
		return true;
	}
	for(int i = 0; i < this->nrows; i++){
		for(int j = 0; j < this->ncols; j++){
			if(this->data[i][j] != other[i][j]){
				return true;
			}
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, Matrix m){
	for(int i = 0; i < m.nrows; i++){
		for(int j = 0; j < m.ncols; j++){
			os << m.data[i][j] << ", ";
		}
		os << std::endl;
	}
	return os;
}

void Matrix::print(){
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < ncols; j++){
			std::cout << data[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

int Matrix::get_nrows(){
	return this->nrows;
}

int Matrix::get_ncols(){
	return this->ncols;
}

Matrix transpose(Matrix m){
	Matrix n(m.get_ncols(), m.get_nrows());
	for(int i = 0; i < m.get_nrows(); i++){
		for(int j = 0; j < m.get_ncols(); j++){
			n[j][i] = m[i][j];
		}
	}
	return n;
}
