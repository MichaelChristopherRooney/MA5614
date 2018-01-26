#include <iostream>

#define LIMIT 0.0000001
#define MAX_ITER 1000

// The loop will terminate if the next value in the series is below LIMIT.
// As this point we have decided that the series has converged.
// To protect against non-convergance, MAX_ITER will be used as the iteration limit.
// Note: first two iterations are handled outside for loop.
// For loop starts at i = 2 because of this.
static double exp_part_1(const double x){
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

// Uses exp(x) = (exp(x/2) ^ 2)
static double exp_part_2(const double x){
	double result = exp_part_1(x / 2.0);
	result = result * result;
	return result;
}

// This recursively calls itself with x = x/2 while x is outside a certain range.
// Once x is within a certain range it calculates exp(x).
// Then as each recursie call returns the result is squared and returned.
static double exp_part_3(const double x){
	double result;
	if(x >= -1.0 && x <= 1){
		result = exp_part_1(x / 2.0); // x within range, calulcate exp(x)
	} else {
		result = exp_part_3(x / 2.0); // call itself
	}
	result = result * result;
	return result;
}

// README
// This calculates exp(x) for several x values using three different approaches.
// The approaches are described in the parts of the assignment.
// Part 1 just uses the series to calculate exp(x).
// Part 2 uses exp(x) = exp(x/2) ^ 2
// Part 3 is the same as part 2 but is recursive.
// The estimate each part gives for exp(x) is printed.
// Note that some estimates will be wrong to show that the part is not suitable for such values.
// The actual value of exp(x) is also printed as a comparison.
int main(void){
	const double xs[] = { 0, 0.5, 1, 25, -25, 50, -50 };
	const double actual_results[] = { 1, 1.64872, 2.71828, 72004899337.4, 1.38879E-11, 5.184705E21, 1.928749E-22};
	for(int i = 0; i < sizeof(xs) / sizeof(xs[0]); i++){
		double result_1 = exp_part_1(xs[i]);
		double result_2 = exp_part_2(xs[i]);
		double result_3 = exp_part_3(xs[i]);
		std::cout << "x = " << xs[i] << std::endl;
		std::cout << "Actual result: " << actual_results[i] << std::endl;
		std::cout << "Part one result: " << result_1 << std::endl;
		std::cout << "Part two result: " << result_2 << std::endl;
		std::cout << "Part three result: " << result_3 << std::endl;
		std::cout << "=========================================" << std::endl;
	}
}

