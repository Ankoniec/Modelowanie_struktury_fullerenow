#include "fun.h"
#define M_PI 3.14159265359



vector<double> Fulleren::PairCorrelationFunction(int M) {
	size_t n = r.size();
	vector<double> pcf(M,0.0);
	double r_sr = MeanRadius();
	double omega = 4 * M_PI * r_sr;
	double r_max = 2.5 * r_sr;
	double dr = r_max / M;
	double k = 0;
	double r, m;

	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j) {
			if (i != j) {
				vector<double> r_ij{
				x[j] - x[i],
				y[j] - y[i],
				z[j] - z[i]
				};

				r = sqrt(pow(r_ij[0], 2) + pow(r_ij[1], 2) + pow(r_ij[2], 2));
				m = floor(r / dr);
				if (m < M) pcf[(int)m] += 2 * 4 * M_PI * r_sr * r_sr / (n * n * 2 * M_PI * r * dr);
			}
		}
	}
	return pcf;

}