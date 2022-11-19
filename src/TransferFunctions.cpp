#include "TransferFunctions.h"

glm::vec3 nl_sRGB_to_sRGB_Fast(const glm::vec3& color)
{
	return glm::vec3(glm::pow(color, glm::vec3(2.2)));
}

glm::vec3 sRGB_to_nl_sRGB_Fast(const glm::vec3& color)
{
	return glm::pow(color, glm::vec3(1.0/2.2));
}

glm::vec3 nl_sRGB_to_sRGB(const glm::vec3& color)
{
	glm::vec3 result;

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 0.04045)
		{
			result[i] = color[i] / 12.92;
		}
		else
		{
			result[i] = glm::pow((color[i] + 0.055) / 1.055, 2.4);
		}
	}

	return result;
}

glm::vec3 sRGB_to_nl_SRGB(const glm::vec3& color)
{
	glm::vec3 result;

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 0.0031308)
		{
			result[i] = color[i] * 12.92;
		}
		else
		{
			result[i] = 1.055 * glm::pow(color[i], 1.0 / 2.4) - 0.055;
		}
	}

	return result;
}

glm::vec3 nl_REC709_to_REC709(const glm::vec3& color)
{
	glm::vec3 result;

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 0.081)
		{
			result[i] = color[i] / 4.5;
		}
		else
		{
			result[i] = glm::pow((color[i] + 0.099) / 1.099, 2.2);
		}
	}

	return result;
}

glm::vec3 REC709_to_nl_REC709(const glm::vec3& color)
{
	glm::vec3 result;

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 0.0018)
		{
			result[i] = color[i] * 4.5;
		}
		else
		{
			result[i] = 1.099 * glm::pow(color[i], 1.0 / 2.2) - 0.099;
		}
	}

	return result;
}

glm::vec3 PQ_to_REC2020(const glm::vec3& color)
{
	glm::vec3 result;

	const double m1 = 2610.0 / 16384.0;
	const double m2 = 2523.0 / 4096.0 * 128.0;
	const double c1 = 3424.0 / 4096.0;
	const double c2 = 2413.0 / 4096.0 * 32.0;
	const double c3 = 2392.0 / 4096.0 * 32.0;

	for (size_t i = 0; i < 3; i++)
	{
		double Y = glm::pow(color[i], 1.0 / m2);
		double a = glm::max(Y - c1, 0.0);
		double b = c2 - c3 * Y;
		double Ym = glm::pow(a / b, 1.0 / m1);

		result[i] = 10000.0 * Ym;
	}

	return result;
}

glm::vec3 REC2020_to_PQ(const glm::vec3& color)
{
	glm::vec3 result;

	const double m1 = 2610.0 / 16384.0;
	const double m2 = 2523.0 / 4096.0 * 128.0;
	const double c1 = 3424.0 / 4096.0;
	const double c2 = 2413.0 / 4096.0 * 32.0;
	const double c3 = 2392.0 / 4096.0 * 32.0;

	for (size_t i = 0; i < 3; i++)
	{
		double Y = color[i] / 10000.0;
		double Ym1 = glm::pow(Y, m1);

		result[i] = glm::pow((c1 + c2 * Ym1) / (1.0 + c3 * Ym1), m2);
	}

	return result;
}

glm::vec3 HLG_to_REC2020(const glm::vec3& color)
{
	glm::vec3 result;

	const double a = 0.17883277;
	const double b = 1.0 - 4.0 * a;
	const double c = 0.5 - a * glm::log(4.0 * a);

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 1.0 / 12.0)
		{
			result[i] = glm::sqrt(3.0 * color[i]);
		}
		else
		{
			result[i] = a * glm::log(12.0 * color[i] - b) + c;
		}
	}

	return result;
}

glm::vec3 REC2020_to_HLG(const glm::vec3& color)
{
	glm::vec3 result;

	const double a = 0.17883277;
	const double b = 1.0 - 4.0 * a;
	const double c = 0.5 - a * glm::log(4.0 * a);

	for (size_t i = 0; i < 3; i++)
	{
		if (color[i] <= 0.5)
		{
			result[i] = (color[i] * color[i]) / 3.0;
		}
		else
		{
			result[i] = 1.0 / 12.0 * (b + glm::exp((color[i] - c) / a));
		}
	}

	return result;
}
