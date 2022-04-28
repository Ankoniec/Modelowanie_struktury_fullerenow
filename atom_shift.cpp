#include "fun.h"

void Fulleren::atom_shift(size_t i, double w_r, double w_fi, double w_th, double beta) {
	double U1 = uniform(), U2 = uniform(), U3 = uniform(), U4 = uniform();
	double dr = r[i] * (2 * U1 - 1) * w_r;
	double dfi = fi[i] * (2 * U2 - 1) * w_fi;
	double dth = th[i] * (2 * U3 - 1) * w_th;

}