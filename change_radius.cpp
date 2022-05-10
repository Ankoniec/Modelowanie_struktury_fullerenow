#include <iostream>
#include "fun.h"

using namespace std;


void Fulleren::change_global_radius(double W_all, double beta) {
	double U1 = uniform(), U2 = uniform();
	size_t atoms_num = x.size();

	vector<double> r_old;
	for (size_t atom = 0; atom < atoms_num; ++atom) {
		r_old.push_back(r[atom]);
	}

	double E_old = total_energy();

	for (size_t atom = 0; atom < atoms_num; ++atom) {
		r[atom] = r_old[atom] * (1 + W_all * (2 * U1 - 1));
	}

	for (size_t atom = 0; atom < atoms_num; ++atom) {
		x[atom] = r[atom] * sin(th[atom]) * cos(fi[atom]);
		y[atom] = r[atom] * sin(th[atom]) * sin(fi[atom]);
		z[atom] = r[atom] * cos(th[atom]);
	}

	double E_new = total_energy();
	double p_acc = min(1.0, exp(-beta * (E_new - E_old)));

	if (U2 > p_acc) {
		for (size_t atom = 0; atom < atoms_num; ++atom) {
			r[atom] = r_old[atom];
			x[atom] = r[atom] * sin(th[atom]) * cos(fi[atom]);
			y[atom] = r[atom] * sin(th[atom]) * sin(fi[atom]);
			z[atom] = r[atom] * cos(th[atom]);
		}
	}
}