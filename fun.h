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
		double B(size_t i, size_t j);
		double BrennerPotential(size_t i);
		double TotalEnergy();
		double MeanRadius();
		void SetInitialPositions(size_t n_atoms, double R);
		void AtomShift(size_t i, double w_r, double w_fi, double w_th, double beta);
		void ChangeGlobalRadius(double W_all, double beta);
		vector<double> PairCorrelationFunction(int M);
};

double uniform();
double calc_beta(double min, double max, double i, double i_max, double p);