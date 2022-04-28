#include "fun.h"
#define M_PI 3.14159265359

using namespace std;

void Fulleren::atom_shift(size_t i, double w_r, double w_fi, double w_th, double beta) {
	double U1 = uniform(), U2 = uniform(), U3 = uniform(), U4 = uniform();
	double dr = r[i] * (2 * U1 - 1) * w_r;
	double dfi = fi[i] * (2 * U2 - 1) * w_fi;
	double dth = th[i] * (2 * U3 - 1) * w_th;

	double V_old = brenner_potential(i);

	bool changed_th = true;
	bool changed_fi = true;

	r[i] += dr;
	fi[i] += dfi;
	th[i] += dth;

	if (fi[i] < 0 || fi[i] > 2 * M_PI) {
		fi[i] += 2 * M_PI;
		changed_fi = false;
	}
	if (th[i] < 0 || th[i] > M_PI) {
		th[i] -= dth;
		changed_th = false;
	}

	x[i] = r[i] * sin(th[i]) * cos(fi[i]);
	y[i] = r[i] * sin(th[i]) * sin(fi[i]);
	z[i] = r[i] * cos(th[i]);

	double V_new = brenner_potential(i);

	double p_acc = min(1.0, exp(-beta * (V_new - V_old)));

	if (U4 > p_acc) {
		r[i] -= dr;
		if(changed_fi) fi[i] -= dfi; // TODO: problem ze zmiana wartosci
		if(changed_th) th[i] -= dth;
	}

}