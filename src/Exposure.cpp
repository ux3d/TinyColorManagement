#include "Exposure.h"

#include <glm/glm.hpp>

double calculateEV100(double N, double t, double S)
{
	double N2 = N * N;

	return glm::log2((N2/t) * (100.0/S));
}

double Yavg_2_EV100(double Yavg)
{
	return glm::log2(Yavg * 8.0);
}

double EV100_2_Yavg(double ev100)
{
	return glm::pow(2.0, ev100 - 3.0);
}

double EV100_2_Ymax(double ev100)
{
	return 1.2 * glm::pow(2.0, ev100);
}

double EV100_2_EXPOSURE(double ev100)
{
	return 1.0 / EV100_2_Ymax(ev100);
}
