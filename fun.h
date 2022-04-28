#pragma once
#include <functional>
#include <vector>

using namespace std;

class Fulleren {
	public:
		vector<double> x;
		vector<double> y;
		vector<double> z;
		vector<double> r;
		vector<double> fi;
		vector<double> th;

		double f_cut(double r);
		double brenner_potential(size_t i);
		double total_energy();
		void atom_shift(size_t i, double w_r, double w_fi, double w_th, double beta);
};

double uniform();

double calc_beta(double min, double max, double i, double i_max, double p);