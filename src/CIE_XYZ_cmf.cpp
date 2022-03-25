#include "CIE_XYZ_cmf.h"

glm::vec3 WAVELENGTH_2_XYZ(double wavelength)
{
	if (wavelength < cmf1931.front().wavelength || wavelength > cmf1931.back().wavelength)
	{
		return glm::vec3(0.0, 0.0, 0.0);
	}

	size_t start = 0;
	size_t end = cmf1931.size() - 1;
	while (start + 1 < end)
	{
		size_t pivot = (start + end) / 2;

		if (wavelength < cmf1931[pivot].wavelength)
		{
			end = pivot;
		}
		else if (wavelength > cmf1931[pivot].wavelength)
		{
			start = pivot;
		}
		else
		{
			// Direct match
			return cmf1931[pivot].XYZ;
		}
	}

	double weight = (wavelength - cmf1931[start].wavelength) / (cmf1931[end].wavelength - cmf1931[start].wavelength);

	return glm::mix(cmf1931[start].XYZ, cmf1931[end].XYZ, weight);
}
