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

	double num;
	int i = 0;

	ifstream indata;
	indata.open("atoms_positions_60.dat");

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
	cout << "Simulation result:" << test.TotalEnergy() << endl;
	if (abs(test.TotalEnergy() + 421.6) < 1) cout << "Test passed :-DDD" << endl;
	else cout << "Test failed" << endl;


	// SIMULATION
	size_t n_atoms = 60;
	Fulleren simulation;

	// parameters to calculate beta
	double beta;
	double beta_min = 1.0, beta_max = 100.0, p = 2.0;

	// parameters for shifting atoms
	double w_r = pow(10, -4), w_fi = 0.05, w_th = 0.05, W_all = pow(10, -4);

	// initial atoms' radius
	double R_i = 3.5;

	int it_max = pow(10, 5), M = 100;
	double energy;

	ofstream beta_file;
	ofstream energy_file;
	ofstream xyz_file;
	ofstream histogram_file;
	beta_file.open("C:\\Users\\AnnaMaria\\source\\repos\\MonteCarlo2\\simulation_data\\beta_iter_4.txt");
	energy_file.open("C:\\Users\\AnnaMaria\\source\\repos\\MonteCarlo2\\simulation_data\\energy_iter_4.txt");
	xyz_file.open("C:\\Users\\AnnaMaria\\source\\repos\\MonteCarlo2\\simulation_data\\atoms_coordinates_4.txt");
	histogram_file.open("C:\\Users\\AnnaMaria\\source\\repos\\MonteCarlo2\\simulation_data\\histogram_4.txt");

	simulation.SetInitialPositions(n_atoms, R_i);

	for (int it = 0; it < it_max; ++it) {

		beta = calc_beta(beta_min, beta_max, it, it_max, p);
		energy = simulation.TotalEnergy();

		for (size_t atom = 0; atom < n_atoms; ++atom) {
			simulation.AtomShift(atom, w_r, w_fi, w_th, beta);
		}

		simulation.ChangeGlobalRadius(W_all, beta);

		if (it % 100 == 0) {
			cout << "Iteration: " << it << " | Beta: " << beta;
			cout << "| V_total:" << energy << endl;
			beta_file << it << " " << beta << endl;
			energy_file << it << " " << energy << endl;
		}
	}

	for (size_t atom = 0; atom < n_atoms; ++atom) {
		xyz_file << simulation.x[atom] << " " << simulation.y[atom] << " " << simulation.z[atom] << endl;
	}

	cout << "Total energy of the structure: " << simulation.TotalEnergy() << endl;
	cout << "Mean atoms' radius: " << simulation.MeanRadius() << endl;

	vector<double> PCF = simulation.PairCorrelationFunction(M);
	for (double pcf_m : PCF) histogram_file << pcf_m << endl;

}