#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <functional>
#include "fun.h"

using namespace std;


double uniform() {
	return (rand() / (double)RAND_MAX);
}


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
	fulleren sim_fulleren;
	double beta_min = 1.0;
	double beta_max = 100.0;


}