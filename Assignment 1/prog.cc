#include <iostream>

#define LIMIT 100

// Note: first two iterations are handled outside for loop.
// For loop starts at i = 2 because of this.
double exp_part_1(double x){
	double result = 1.0 + x;
	double x_power = x;
	double div = 1;
	for(int i = 2; i < LIMIT; i++){
		x_power = x_power * x;
		div = div * i;
		result = result + (x_power / div);
	}
	return result;
}

double exp_part_2(double x){
	double result = exp_part_1(x / 2.0);
	result = result * result;
	return result;
}

// TODO: comment
// TODO: cutoff is pretty arbitrary right now
double exp_part_3(double x){
	double result;
	if(x >= -1.0 && x <= 1){
		result = exp_part_1(x / 2.0);
	} else {
		result = exp_part_3(x / 2.0);
	}
	result = result * result;
	return result;
}

int main(void){
	double x = -50.0;
	double result = exp_part_1(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;
	result = exp_part_2(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;
	result = exp_part_3(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;

}

