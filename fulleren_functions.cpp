#include <iostream>
#include "fun.h"
#define M_PI 3.14159265359

using namespace std;

double Fulleren::f_cut(double r) {
	double R1 = 1.7;
	double R2 = 2.0;
	if (r <= R1) return 1.0;
	if (r <= R2 && r > R1) return (1 + cos((r - R1) * M_PI / (R2 - R1))) / 2;
	if (r > R2) return 0;
}

double Fulleren::total_energy() {
	size_t atoms_num = x.size();
	double V_tot = 0.0;

	for (size_t i = 0; i < atoms_num; ++i) {
		V_tot += brenner_potential(i);
	}
	return V_tot / 2;
}

double Fulleren::mean_radius() {
	size_t atoms_num = x.size();
	double r_sr = 0;

	for (double dr : r) r_sr += dr;

	return r_sr / atoms_num;
}