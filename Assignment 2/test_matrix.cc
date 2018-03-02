#include <iostream>

#include "matrix.h"

void test_accessors_and_mutators(){
	const double SET_VALUE_ONE = 2.0;
	const double SET_VALUE_TWO = 3.0;
	const double SET_VALUE_THREE = 3.0;
	Matrix m (2, 3);
	// First use set() and get()
	m.set(1, 1, SET_VALUE_ONE);
	if(m.get(1, 1) == SET_VALUE_ONE){
		std::cout << "SUCCESS: set() and get() worked correctly\n";
	} else { 
		std::cout << "ERROR: set() and get() did not work correctly\n";
	}
	// Now use [] 
	m[1][1] = SET_VALUE_TWO;
	if(m[1][1] == SET_VALUE_TWO){
		std::cout << "SUCCESS: [] overload worked correctly\n";
	} else { 
		std::cout << "ERROR: [] overload did not work correctly\n";
		return;
	}
	// Now use ()
	m(1, 1) = SET_VALUE_THREE;
	if(m(1, 1) == SET_VALUE_THREE){
		std::cout << "SUCCESS: () overload worked correctly\n";
	} else { 
		std::cout << "ERROR: () did not work correctly\n";
		return;
	}
}

void test_assignment(){
	const double VALUE = 2.0;
	Matrix m1 (2, 3);
	m1.set(1, 1, VALUE);
	Matrix m2 = m1;
	if(m1.get(1, 1) == m2.get(1, 1)){
		std::cout << "SUCCESS: = overload worked correctly\n";
	} else {
		std::cout << "ERROR: = overload did not work correctly\n";
	}
}

void test_addition(){
	const double VALUE = 2.0;
	// First test m3 = m2 + m1
	Matrix m1 (2, 3);
	m1.set(1, 1, VALUE);
	Matrix m2 = m1;
	Matrix m3 = m2 + m1;
	if(m3.get(1, 1) == VALUE * 2){
		std::cout << "SUCCESS: + overload worked correctly\n";
	} else {
		std::cout << "ERROR: + overload did not work correctly\n";
	}
	// Now test m2 += m1
	m2 += m1;
	if(m2.get(1, 1) == VALUE * 2){
		std::cout << "SUCCESS: += overload worked correctly\n";
	} else {
		std::cout << "ERROR: += overload did not work correctly\n";
	}
}

void test_subtraction(){
	const double VALUE_1 = 2.0;
	const double VALUE_2 = 3.0;
	// First test m3 = m2 - m1
	Matrix m1 (2, 3);
	m1.set(1, 1, VALUE_1);
	Matrix m2 (2, 3);
	m2.set(1, 1, VALUE_2);
	Matrix m3 = m2 - m1;
	if(m3.get(1, 1) == VALUE_2 - VALUE_1){
		std::cout << "SUCCESS: - overload worked correctly\n";
	} else {
		std::cout << "ERROR: - overload did not work correctly\n";
	}
	// Now test m2 -= m1
	m2 -= m1;
	if(m2.get(1, 1) == VALUE_2 - VALUE_1){
		std::cout << "SUCCESS: -= overload worked correctly\n";
	} else {
		std::cout << "ERROR: -= overload did not work correctly\n";
	}
}

void test_multiplication(){
	const double VALUE = 2.0;
	// First do m3 = m2 * m1
	Matrix m1(1, 2);
	m1[0][0] = VALUE;
	Matrix m2(2, 1);
	m2[0][0] = VALUE;
	Matrix m3 = m2 * m1;
	if(m3[0][0] == VALUE * 2){
		std::cout << "SUCCESS: * overload worked correctly\n";
	} else {
		std::cout << "ERROR: * overload did not work correctly\n";
	}
	// Now do m2 *= m1
	m2 *= m1;
	if(m2[0][0] == VALUE * 2){
		std::cout << "SUCCESS: *= overload worked correctly\n";
	} else {
		std::cout << "ERROR: *= overload did not work correctly\n";
	}
}

void test_equality(){
	// First they should be equal
	Matrix m1(1, 2);
	Matrix m2(1, 2);
	if(m1 == m2){
		std::cout << "SUCCESS: == overload worked correctly\n";
	} else {
		std::cout << "ERROR: == overload did not work correctly\n";
	}
	// Now test to check they are not equal
	m2[0][0] = 3.0;
	if(m1 != m2){
		std::cout << "SUCCESS: != overload worked correctly\n";
	} else {
		std::cout << "ERROR: != overload did not work correctly\n";
	}
}

void test_transpose(){
	Matrix m1(2, 3);
	m1[0][0] = 0.0;
	m1[0][1] = 1.0;
	m1[0][2] = 2.0;
	m1[1][0] = 3.0;
	m1[1][1] = 4.0;
	m1[1][2] = 5.0;
	Matrix m2 = transpose(m1);
	if(m2[0][0] == 0.0 && m2[2][1] == 5.0 && m2[1][0] == 1.0){
		std::cout << "SUCCESS: transpose() worked correctly\n";
	} else {
		std::cout << "ERROR: transpose() did not work correctly\n";
	}
}

void test_printing(){
	Matrix m(2, 2);
	m[0][0] = 1.0;
	m[0][1] = 2.0;
	m[1][0] = 3.0;
	m[1][1] = 4.0;
	std::cout << "Printing with << overload:\n" << m;
	std::cout << "Printing with print() member function:\n";
	m.print();
}

int main(void){
	test_accessors_and_mutators();
	test_assignment();
	test_addition();
	test_subtraction();
	test_multiplication();
	test_equality();
	test_transpose();
	test_printing();
	return 0;
}
