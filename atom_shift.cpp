#include <iostream>
#include "fun.h"
#define M_PI 3.14159265359

using namespace std;

void Fulleren::atom_shift(size_t i, double w_r, double w_fi, double w_th, double beta) {
	double U1 = uniform(), U2 = uniform(), U3 = uniform(), U4 = uniform();
	double dr = r[i] * (2 * U1 - 1) * w_r;
	double dfi = fi[i] * (2 * U2 - 1) * w_fi;
	double dth = th[i] * (2 * U3 - 1) * w_th;

	double V_old = brenner_potential(i);

	vector<double> old_coordinates{ r[i],fi[i],th[i],x[i],y[i],z[i] };

	r[i] += dr;
	fi[i] += dfi;
	th[i] += dth;

	if (fi[i] < 0 || fi[i] > 2 * M_PI) fi[i] += 2 * M_PI;
	if (th[i] < 0 || th[i] > M_PI) th[i] -= dth;

	x[i] = r[i] * sin(th[i]) * cos(fi[i]);
	y[i] = r[i] * sin(th[i]) * sin(fi[i]);
	z[i] = r[i] * cos(th[i]);

	double V_new = brenner_potential(i);
	double p_acc = min(1.0, exp(-beta * (V_new - V_old)));

	if (U4 > p_acc) {
		r[i] = old_coordinates[0];
		fi[i] = old_coordinates[1];
		th[i] = old_coordinates[2];
		x[i] = old_coordinates[3];
		y[i] = old_coordinates[4];
		z[i] = old_coordinates[5];
	}

}