#include <vector>

// TODO: destructor

class Matrix {
public:
	Matrix(int nrows, int ncols);
	void set(const int row, const int col, const double val);
	double get(const int row, const int col) const;
	void print();
	std::vector<double>& operator[](const int row);
	Matrix& operator=(const Matrix& m);
	Matrix operator+(const Matrix& other);
	void operator+=(const Matrix& other);	
	Matrix operator*(const Matrix& other);
	void operator*=(const Matrix& other);
	double& operator()(const int row, const int col);
	int get_nrows();
	int get_ncols();
private:
	int nrows;
	int ncols;
	std::vector<std::vector<double> > data;
	Matrix(); // disable default constructor
	//~Matrix(); // disable default destructor
};

// Not a member function, declare outside class
Matrix transpose(Matrix m);
