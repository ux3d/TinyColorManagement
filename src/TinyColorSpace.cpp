#include "TinyColorSpace.h"

glm::vec3 XYZ_2_xyY(glm::vec3 XYZ)
{
	glm::vec3 xyY;

	double divisor = XYZ[0] + XYZ[1] + XYZ[2];
	if (divisor == 0.0)
	{
		divisor = 1e-10;
	}

	xyY[0] = XYZ[0] / divisor;
	xyY[1] = XYZ[1] / divisor;
	xyY[2] = XYZ[1];

	return xyY;
}

glm::vec3 xyY_2_XYZ(glm::vec3 xyY)
{
	glm::vec3 XYZ;

	XYZ[0] = xyY[0] * xyY[2] / glm::max((double)xyY[1], 1e-10);
	XYZ[1] = xyY[2];
	XYZ[2] = (1.0 - xyY[0] - xyY[1]) * xyY[2] / glm::max((double)xyY[1], 1e-10);

	return XYZ;
}

//

glm::mat3 RGB_2_XYZ(const Chromaticities& chroma, double Y)
{
	// X and Z values of RGB value (1, 1, 1), or "white"

	double X = chroma.white.x * Y / chroma.white.y;
	double Z = (1 - chroma.white.x - chroma.white.y) * Y / chroma.white.y;

	// Scale factors for matrix rows

	double d = chroma.red.x   * (chroma.blue.y  - chroma.green.y) +
				chroma.blue.x  * (chroma.green.y - chroma.red.y) +
				chroma.green.x * (chroma.red.y   - chroma.blue.y);

	double Sr = (X * (chroma.blue.y - chroma.green.y) -
				chroma.green.x * (Y * (chroma.blue.y - 1) +
				chroma.blue.y  * (X + Z)) +
				chroma.blue.x  * (Y * (chroma.green.y - 1) +
				chroma.green.y * (X + Z))) / d;

	double Sg = (X * (chroma.red.y - chroma.blue.y) +
				chroma.red.x   * (Y * (chroma.blue.y - 1) +
				chroma.blue.y  * (X + Z)) -
				chroma.blue.x  * (Y * (chroma.red.y - 1) +
				chroma.red.y   * (X + Z))) / d;

	double Sb = (X * (chroma.green.y - chroma.red.y) -
				chroma.red.x   * (Y * (chroma.green.y - 1) +
				chroma.green.y * (X + Z)) +
				chroma.green.x * (Y * (chroma.red.y - 1) +
				chroma.red.y   * (X + Z))) / d;

	// Assemble the matrix

	glm::mat3 M;

	M[0][0] = Sr * chroma.red.x;
	M[0][1] = Sr * chroma.red.y;
	M[0][2] = Sr * (1 - chroma.red.x - chroma.red.y);

	M[1][0] = Sg * chroma.green.x;
	M[1][1] = Sg * chroma.green.y;
	M[1][2] = Sg * (1 - chroma.green.x - chroma.green.y);

	M[2][0] = Sb * chroma.blue.x;
	M[2][1] = Sb * chroma.blue.y;
	M[2][2] = Sb * (1 - chroma.blue.x - chroma.blue.y);

	return M;
}

glm::mat3 XYZ_2_RGB(const Chromaticities& chroma, double Y)
{
    return glm::inverse(RGB_2_XYZ(chroma, Y));
}

//

glm::mat3 chromaticAdaptationMatrix(const glm::vec2& source, const glm::vec2& destination)
{
	const glm::mat3 ConeResponseBradford = {
		   0.89510, -0.75020,  0.03890,
		   0.26640,  1.71350, -0.06850,
		  -0.16140,  0.03670,  1.02960
	};

	glm::vec3 source_xyY = glm::vec3(source, 1.0);
	glm::vec3 destination_xyY = glm::vec3(destination, 1.0);

	glm::vec3 source_XYZ = xyY_2_XYZ(source_xyY);
	glm::vec3 destination_XYZ = xyY_2_XYZ(destination_xyY);

	//

	glm::vec3 source_RhoGammaBeta = ConeResponseBradford * source_XYZ;
	glm::vec3 destination_RhoGammaBeta = ConeResponseBradford * destination_XYZ;

	glm::mat3 Ma = glm::mat3(
	      destination_RhoGammaBeta[0] / source_RhoGammaBeta[0], 0.0, 0.0,
	      0.0, destination_RhoGammaBeta[1] / source_RhoGammaBeta[1], 0.0,
	      0.0, 0.0, destination_RhoGammaBeta[2] / source_RhoGammaBeta[2]
	);

	return glm::inverse(ConeResponseBradford) * Ma * ConeResponseBradford;
};

glm::mat3 saturationMatrix(double sat, glm::vec3 rgb2Y)
{
	//
	// This function determines the terms for a 3x3 saturation matrix that is
	// based on the luminance of the input.
	//
	glm::mat3 M;

	M[0][0] = (1.0 - sat) * rgb2Y[0] + sat;
	M[1][0] = (1.0 - sat) * rgb2Y[0];
	M[2][0] = (1.0 - sat) * rgb2Y[0];

	M[0][1] = (1.0 - sat) * rgb2Y[1];
	M[1][1] = (1.0 - sat) * rgb2Y[1] + sat;
	M[2][1] = (1.0 - sat) * rgb2Y[1];

	M[0][2] = (1.0 - sat) * rgb2Y[2];
	M[1][2] = (1.0 - sat) * rgb2Y[2];
	M[2][2] = (1.0 - sat) * rgb2Y[2] + sat;

	M = glm::transpose(M);

	return M;
}

//

glm::vec3 nlSRGB_2_SRGB_Fast(const glm::vec3& color)
{
	return glm::vec3(glm::pow(color, glm::vec3(2.2)));
}

glm::vec3 SRGB_2_nlSRGB_Fast(const glm::vec3& color)
{
	return glm::pow(color, glm::vec3(1.0/2.2));
}

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_SRGB

glm::vec3 nlSRGB_2_SRGB(const glm::vec3& color)
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

glm::vec3 SRGB_2_nlSRGB(const glm::vec3& color)
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

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_BT1886

glm::vec3 nlREC709_2_REC709(const glm::vec3& color)
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

glm::vec3 REC709_2_nlREC709(const glm::vec3& color)
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

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_PQ

glm::vec3 PQ_2_REC2020(const glm::vec3& color)
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

glm::vec3 REC2020_2_PQ(const glm::vec3& color)
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

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_HLG

glm::vec3 HLG_2_REC2020(const glm::vec3& color)
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

glm::vec3 REC2020_2_HLG(const glm::vec3& color)
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
