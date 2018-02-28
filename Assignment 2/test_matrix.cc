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
		std::cout << "SUCCESS: Element at [1, 1] set and retrieved correctly using set() and get()\n";
	} else { 
		std::cout << "ERROR: Element at [1, 1] NOT set and retrieved correctly using set() and get()\n";
	}
	// Now use [] 
	m[1][1] = SET_VALUE_TWO;
	if(m[1][1] == SET_VALUE_TWO){
		std::cout << "SUCCESS: Element at [1, 1] set and retrieved correctly using []\n";
	} else { 
		std::cout << "ERROR: Element at [1, 1] NOT set and retrieved correctly using []\n";
		return;
	}
	// Now use ()
	m(1, 1) = SET_VALUE_THREE;
	if(m(1, 1) == SET_VALUE_THREE){
		std::cout << "SUCCESS: Element at [1, 1] set and retrieved correctly using ()\n";
	} else { 
		std::cout << "ERROR: Element at [1, 1] NOT set and retrieved correctly using ()\n";
		return;
	}
}

int main(void){
	test_accessors_and_mutators();
	return 0;
}
