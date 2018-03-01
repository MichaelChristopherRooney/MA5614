#include <vector>
#include <iostream>

// TODO: destructor

class Matrix {
public:
	Matrix(int nrows, int ncols);
	void set(const int row, const int col, const double val);
	double get(const int row, const int col) const;
	void print() const;
	std::vector<double>& operator[](const int row);
	const std::vector<double> operator[](const int row) const;
	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& other) const;
	void operator+=(const Matrix& other);	
	Matrix operator-(const Matrix& other) const;
	void operator-=(const Matrix& other);	
	Matrix operator*(const Matrix& other) const;
	void operator*=(const Matrix& other);
	double& operator()(const int row, const int col);
	double operator()(const int row, const int col) const;
	bool operator==(const Matrix &other) const;
	bool operator!=(const Matrix &other) const;
	int get_nrows() const;
	int get_ncols() const;
	friend std::ostream& operator<<(std::ostream& os, Matrix m);
private:
	int nrows;
	int ncols;
	std::vector<std::vector<double> > data;
	Matrix(); // disable default constructor
	//~Matrix(); // disable default destructor
};

// Non-member functions, declare outside class
Matrix transpose(Matrix m);
