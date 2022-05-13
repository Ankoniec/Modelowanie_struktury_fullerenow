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
	cout << "**** Brenner Potential function test ****" << endl;
	cout << "Theoretical value: -421.6" << endl;
	cout << "Simulation result:" << test.total_energy() << endl;
	if (abs(test.total_energy() + 421.6) < 1) cout << "Test passed" << endl;
	else cout << "Test failed" << endl;


	// SIMULATION
	size_t n = 60;
	Fulleren simulation;
	double beta;
	double beta_min = 1.0, beta_max = 100.0, p = 2.0;
	double w_r = pow(10, -4), w_fi = 0.05, w_th = 0.05, W_all = pow(10, -4);
	double R_i = 3.5;
	int it_max = pow(10, 5), M = 100;
	double energy;

	ofstream beta_file;
	ofstream energy_file;
	ofstream xyz_file;
	ofstream histogram_file;
	beta_file.open("beta_iter.txt");
	energy_file.open("energy_iter.txt");
	xyz_file.open("atoms_coordinates.txt");
	histogram_file.open("histogram.txt");

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
		energy = simulation.total_energy();

		for (size_t atom = 0; atom < n; ++atom) {
			simulation.atom_shift(atom, w_r, w_fi, w_th, beta);
		}

		simulation.change_global_radius(W_all, beta);

		if (it % 100 == 0) {
			cout << "Iteration: " << it << " | Beta: " << beta;
			cout << "| V_total:" << energy << endl;
			beta_file << it << " " << beta << endl;
			energy_file << it << " " << energy << endl;
		}
	}

	for (size_t atom = 0; atom < n; ++atom) {
		xyz_file << simulation.x[atom] << " " << simulation.y[atom] << " " << simulation.z[atom] << endl;
	}

	cout << "Total energy of the structure: " << simulation.total_energy() << endl;
	cout << "Mean atoms' radius: " << simulation.mean_radius() << endl;

	vector<double> PCF = simulation.pair_correlation_function(M);
	for (double pcf_m : PCF) histogram_file << pcf_m << endl;

}