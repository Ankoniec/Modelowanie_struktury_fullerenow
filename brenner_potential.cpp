#include "fun.h"
#define M_PI 3.14159265359


double Fulleren::B(size_t i, size_t j) {
	double delta = 0.80469;
	double a0 = 0.011304;
	double c0 = 19;
	double d0 = 2.5;
	double R_ik, cos_th, g_th;
	double ksi_ij = 0.0;
	size_t n_atoms = x.size();

	vector<double> r_ij{
				x[j] - x[i],
				y[j] - y[i],
				z[j] - z[i]
	};

	double r = sqrt(pow(r_ij[0], 2) + pow(r_ij[1], 2) + pow(r_ij[2], 2));

	for (size_t k = 0; k < n_atoms; ++k) {
		if (k != i && k != j) {

			vector<double> r_ik{
						x[k] - x[i],
						y[k] - y[i],
						z[k] - z[i]
			};

			R_ik = sqrt(pow(r_ik[0], 2) + pow(r_ik[1], 2) + pow(r_ik[2], 2));
			cos_th = (r_ij[0] * r_ik[0] + r_ij[1] * r_ik[1] + r_ij[2] * r_ik[2]) / (r * R_ik);
			g_th = a0 * (1 + pow(c0, 2) / pow(d0, 2) - pow(c0, 2) / (pow(d0, 2) + pow((1 + cos_th), 2)));
			
			if (cos_th > 0) { ksi_ij += 10; }
			else {
				ksi_ij += f_cut(R_ik) * g_th;
			}
		}
	}

	return pow(1 + ksi_ij, -delta);
}


double Fulleren::BrennerPotential(size_t i) {
	double R0 = 1.315; //A
	double De = 6.325; //eV
	double S = 1.29;
	double lambda = 1.5; //1/A
	double Vi = 0.0;

	size_t atoms_num = x.size();
	double V_R, V_A, B_ij;
	double r;

	for (size_t j = 0; j < atoms_num; j++) {

		if (i != j) {

			vector<double> r_ij{
				x[j] - x[i],
				y[j] - y[i],
				z[j] - z[i]
			};

			r = sqrt(pow(r_ij[0], 2) + pow(r_ij[1], 2) + pow(r_ij[2], 2));
			if (r > 2.0) continue;

			V_R = De / (S - 1) * exp(-sqrt(2 * S) * lambda * (r - R0));
			V_A = De * S / (S - 1) * exp(-sqrt(2 / S) * lambda * (r - R0));
			B_ij = ( B(i,j) + B(j,i) ) / 2;
			Vi += f_cut(r) * (V_R - B_ij * V_A);
		}
	}
	return Vi;

}

