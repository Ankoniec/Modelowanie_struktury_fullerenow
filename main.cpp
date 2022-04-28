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

	// READ ATOMS POSITIONS
	cluster test_data;

	ifstream indata;
	indata.open("atoms_positions_60.dat");

	double num;
	int i = 0;

	while (!indata.eof()) {
		if (i > 2) i = 0;
		indata >> num;
		if (i == 0) test_data.x.push_back(num);
		if (i == 1) test_data.y.push_back(num);
		if (i == 2) test_data.z.push_back(num);
		i++;
	}
	indata.close();
	/*
	for (size_t i = 0; i < test_data.x.size(); ++i) {
		test_data.r.push_back(sqrt(
			test_data.x[i] * test_data.x[i] + test_data.y[i] * test_data.y[i] + test_data.z[i] * test_data.z[i]
		));
	}
	*/

	// BRENNER POTENTIAL TEST
	cout << "Test funkcji potencjalu Brennera" << endl;
	cout << "Wartosc teoretyczna: -421.6" << endl;
	cout << "Wynik symulacji:" << Brenner_potential(test_data, &f_cut) << endl;
	if (Brenner_potential(test_data, &f_cut) - 421.6 < 1) cout << "Wynik zgodny z teoria" << endl;
	else cout << "Wynik sprzeczny z teoria" << endl;

}