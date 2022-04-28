#pragma once
#include <functional>
#include <vector>

using namespace std;

struct cluster {
	vector<double> x;
	vector<double> y;
	vector<double> z;
	vector<double> r;
	vector<double> fi;
	vector<double> th;
};

double uniform();
double f_cut(double r);
double Brenner_potential(cluster& c, function<double(double)> f_c);