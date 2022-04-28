#include "fun.h"
#define M_PI 3.14159265359


double f_cut(double r) {
	double R1 = 1.7;
	double R2 = 2.0;
	if (r <= R1) return 1.0;
	if (r <= R2 && r > R1) return (1 + cos((r - R1) * M_PI / (R2 - R1))) / 2;
	if (r > R2) return 0;
}

double Brenner_potential(cluster& c, function<double(double)> f_c) {
	double R0 = 1.315; //A
	double De = 6.325; //eV
	double S = 1.29;
	double lambda = 1.5; //1/A
	double delta = 0.80469;
	double a0 = 0.011304;
	double c0 = 19;
	double d0 = 2.5;

	size_t atoms_num = c.x.size();
	vector<double> V(atoms_num, 0.0);
	double V_tot = 0.0;
	double V_R, V_A;
	double B, B_ij, B_ji, ksi_ij, ksi_ji, R_ik, R_jk;
	double r, cos_th_ik, cos_th_jk, g_ik, g_jk;

	for (size_t i = 0; i < atoms_num; ++i) {
		for (size_t j = 0; j < atoms_num; j++) {

			if (i != j) {

				vector<double> r_ij{
					c.x[j] - c.x[i],
					c.y[j] - c.y[i],
					c.z[j] - c.z[i]
				};

				r = sqrt(pow(r_ij[0], 2) + pow(r_ij[1], 2) + pow(r_ij[2], 2));
				ksi_ij = 0;
				ksi_ji = 0;

				for (size_t k = 0; k < atoms_num; ++k) {

					if (k != i && k != j) {
						vector<double> r_ik{
							c.x[k] - c.x[i],
							c.y[k] - c.y[i],
							c.z[k] - c.z[i]
						};

						vector<double> r_jk{
							c.x[k] - c.x[j],
							c.y[k] - c.y[j],
							c.z[k] - c.z[j]
						};

						R_ik = sqrt(pow(r_ik[0], 2) + pow(r_ik[1], 2) + pow(r_ik[2], 2));
						R_jk = sqrt(pow(r_jk[0], 2) + pow(r_jk[1], 2) + pow(r_jk[2], 2));
						cos_th_ik = (r_ij[0] * r_ik[0] + r_ij[1] * r_ik[1] + r_ij[2] * r_ik[2]) / (r * R_ik);
						cos_th_jk = (-r_ij[0] * r_jk[0] - r_ij[1] * r_jk[1] - r_ij[2] * r_jk[2]) / (r * R_jk);
						g_ik = a0 * (1 + pow(c0, 2) / pow(d0, 2) - pow(c0, 2) / (pow(d0, 2) + pow((1 + cos_th_ik), 2)));
						g_jk = a0 * (1 + pow(c0, 2) / pow(d0, 2) - pow(c0, 2) / (pow(d0, 2) + pow((1 + cos_th_jk), 2)));
						ksi_ij += f_c(R_ik) * g_ik;
						ksi_ji += f_c(R_jk) * g_jk;
					}
				}
				V_R = De / (S - 1) * exp(-sqrt(2 * S) * lambda * (r - R0));
				V_A = De * S / (S - 1) * exp(-sqrt(2 / S) * lambda * (r - R0));
				B_ij = pow((1 + ksi_ij), -delta);
				B_ji = pow((1 + ksi_ji), -delta);
				B = (B_ij + B_ji) / 2;
				V[i] += f_c(r) * (V_R - B * V_A);
			}
		}
	}
	for (double v : V) V_tot += 0.5 * v;
	return V_tot;
}