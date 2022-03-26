#include "Exposure.h"

#include <glm/glm.hpp>

double calculateEV100(double N, double t, double S)
{
	double N2 = N * N;

	return glm::log2((N2/t) * (100.0/S));
}

double EV100_2_EXPOSURE(double ev100)
{
	double Lmax = 1.2 * glm::pow(2.0, ev100);
	return 1.0 / Lmax;
}
