#include "ACES.h"

glm::mat3 saturationMatrix(double sat, glm::vec3 Yrgb)
{
	//
	// This function determines the terms for a 3x3 saturation matrix that is
	// based on the luminance of the input.
	//
	glm::mat3 M;

	M[0][0] = (1.0 - sat) * Yrgb[0] + sat;
	M[1][0] = (1.0 - sat) * Yrgb[0];
	M[2][0] = (1.0 - sat) * Yrgb[0];

	M[0][1] = (1.0 - sat) * Yrgb[1];
	M[1][1] = (1.0 - sat) * Yrgb[1] + sat;
	M[2][1] = (1.0 - sat) * Yrgb[1];

	M[0][2] = (1.0 - sat) * Yrgb[2];
	M[1][2] = (1.0 - sat) * Yrgb[2];
	M[2][2] = (1.0 - sat) * Yrgb[2] + sat;

	M = glm::transpose(M);

	return M;
}

