#include "ColorPrimaries.h"

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

double SRGB_2_Y(const glm::vec3& color)
{
	return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}

double REC709_2_Y(const glm::vec3& color)
{
	return SRGB_2_Y(color);
}
