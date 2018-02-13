#include <vector>

class Matrix {
public:
	Matrix(int nrows, int ncols);
	void print();
private:
	int nrows;
	int ncols;
	std::vector<std::vector<double>> data;
	Matrix(); // disable default constructor
	~Matrix(); // disable default destructor
};
