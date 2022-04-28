#include <stdlib.h>
#include <iostream>

double uniform() {
	return (rand() / (double)RAND_MAX);
}

double calc_beta(double min, double max, double i, double i_max, double p) {
	return min + pow(i / i_max, p) * (max - min);
}