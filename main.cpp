#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <functional>
#include "fun.h"
#define M_PI 3.14159265359

using namespace std;


int main() {

	// READ TEST ATOMS POSITIONS
	Fulleren test;

	ifstream indata;
	indata.open("atoms_positions_60.dat");

	double num;
	int i = 0;

	while (!indata.eof()) {
		if (i > 2) i = 0;
		indata >> num;
		if (i == 0) test.x.push_back(num);
		if (i == 1) test.y.push_back(num);
		if (i == 2) test.z.push_back(num);
		i++;
	}
	indata.close();

	// BRENNER POTENTIAL TEST
	cout << "Test funkcji potencjalu Brennera" << endl;
	cout << "Wartosc teoretyczna: -421.6" << endl;
	cout << "Wynik symulacji:" << test.total_energy() << endl;
	if (abs(test.total_energy() + 421.6) < 1) cout << "Wynik zgodny z teoria" << endl;
	else cout << "Wynik sprzeczny z teoria" << endl;


	// SIMULATION
	size_t n = 60;
	Fulleren simulation;
	double beta;
	double beta_min = 1.0, beta_max = 100.0, p = 2.0;
	double w_r = pow(10, -4), w_fi = 0.05, w_th = 0.05, W_all = pow(10, -4);
	double R_i = 3.5;
	int it_max = pow(10, 3);

	for (size_t i = 0; i < n; ++i) {
		simulation.r.push_back(R_i);
		simulation.fi.push_back(2 * M_PI * uniform());
		simulation.th.push_back(M_PI * uniform());
		simulation.x.push_back(simulation.r[i] * sin(simulation.th[i]) * cos(simulation.fi[i]));
		simulation.y.push_back(simulation.r[i] * sin(simulation.th[i]) * sin(simulation.fi[i]));
		simulation.z.push_back(simulation.r[i] * cos(simulation.th[i]));
	}

	for (int it = 0; it < it_max; ++it) {

		beta = calc_beta(beta_min, beta_max, it, it_max, p);
		

		for (size_t atom = 0; atom < n; ++atom) {
			simulation.atom_shift(atom, w_r, w_fi, w_th, beta);
		}

		simulation.change_global_radius(W_all, beta);

		if (it%100==0) cout << "Iteracja: " << it << " | Beta: " << beta << "| V_total:"<< simulation.total_energy() << endl;
	}
	
	
}