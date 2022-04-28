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

		double Brenner_potential(function<double(double)> f_c);
};

double uniform();
double f_cut(double r);
double calc_beta(double min, double max, double i, double i_max, double p);