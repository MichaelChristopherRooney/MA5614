#include <iostream>

#define LIMIT 0.0000001
#define MAX_ITER 1000

// The loop will terminate if the next value in the series is below LIMIT.
// As this point we have decided that the series has converged.
// To protect against non-convergance, MAX_ITER will be used as the iteration limit.
// Note: first two iterations are handled outside for loop.
// For loop starts at i = 2 because of this.
double exp_part_1(double x){
	double result = 1.0 + x;
	double x_power = x;
	double div = 1;
	for(int i = 2; i < MAX_ITER; i++){
		x_power = x_power * x;
		div = div * i;
		double temp = (x_power / div);
		result = result + (x_power / div);
		if(temp >= LIMIT * -1 && temp <= LIMIT){
			break;
		}
	}
	return result;
}

double exp_part_2(double x){
	double result = exp_part_1(x / 2.0);
	result = result * result;
	return result;
}

// This recursively calls itself with x = x/2 while x is outside a certain range.
// Once x is within a certain range it calculates exp(x).
// Then as each recursie call returns the result is squared and returned.
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
	double x = -50;
	double result = exp_part_1(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;
	result = exp_part_2(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;
	result = exp_part_3(x);
	std::cout << "exp(" << x << ") = " << result << std::endl;

}

