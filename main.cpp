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
	fulleren test;

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
	cout << "Wynik symulacji:" << Brenner_potential(test, &f_cut) << endl;
	if (Brenner_potential(test, &f_cut) - 421.6 < 1) cout << "Wynik zgodny z teoria" << endl;
	else cout << "Wynik sprzeczny z teoria" << endl;

	// SIMULATION
	size_t n = 60;
	fulleren simulation;
	double beta_min = 1.0, beta_max = 100.0, p = 2.0, it_max = pow(10,5);
	double R_i = 3.5;

	for (size_t i = 0; i < n; ++i) {
		simulation.r.push_back(R_i);
		simulation.fi.push_back(2 * M_PI * uniform());
		simulation.th.push_back(M_PI * uniform());
		simulation.x.push_back(simulation.r[0] * sin(simulation.th[0]) * cos(simulation.fi[0]));
		simulation.y.push_back(simulation.r[0] * sin(simulation.th[0]) * sin(simulation.fi[0]));
		simulation.z.push_back(simulation.r[0] * cos(simulation.th[0]));
	}


}