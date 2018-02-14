#include <iostream>

#include "matrix.h"

int main(void){
	Matrix *m = new Matrix(2, 3);
	m->set(1, 1, 2.0);
	std::cout << m->get(1, 1) << std::endl;
	m->print();
	return 0;
}
