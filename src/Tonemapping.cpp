#include "Tonemapping.h"

#include "ACES.h"

glm::vec3 tonemapNone(const glm::vec3& color)
{
	return glm::clamp(color, glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0));
}

glm::vec3 tonemapReinhard(const glm::vec3& color)
{
	return color / (glm::vec3(1.0) + color);
}

glm::vec3 tonemapAces(const glm::vec3& color, ColorSpace colorSpace)
{
	if (colorSpace == ColorSpace_UNKNOWN || colorSpace == ColorSpace_AP0)
	{
		return glm::vec3(0.0, 0.0, 0.0);
	}

	glm::vec3 AP1;

	if (colorSpace != ColorSpace_AP1)
	{
		glm::vec3 XYZ;

		switch (colorSpace)
		{
			case ColorSpace_sRGB:
					XYZ = sRGB_to_XYZ * color;
				break;
			case ColorSpace_REC709:
					XYZ = REC709_to_XYZ * color;
				break;
			case ColorSpace_REC2020:
					XYZ = REC2020_to_XYZ * color;
				break;
			case ColorSpace_AP1:
			default:
					// Unreachable code
				break;
		}

		AP1 = XYZ_to_AP1 * D65_to_D60 * XYZ;
	}

	// ACES tonemapping in AP1 color space

	// RTT_SAT
	AP1 = RRT_SAT * AP1;

	// RRT and ODT fit output between 0.0 and 1.0
    glm::vec3 a = (AP1 + glm::vec3(0.0245786)) * AP1 - glm::vec3(0.000090537);
    glm::vec3 b = (AP1 * glm::vec3(0.983729) + glm::vec3(0.4329510)) * AP1 + glm::vec3(0.238081);

    AP1 = a / b;

	// ODT_SAT
    AP1 = ODT_SAT * AP1;

	//

	glm::vec3 result;

	if (colorSpace != ColorSpace_AP1)
	{
		glm::vec3 XYZ = D60_to_D65 * AP1_to_XYZ * AP1;

		switch (colorSpace)
		{
			case ColorSpace_sRGB:
					result = XYZ_to_sRGB * XYZ;
				break;
			case ColorSpace_REC709:
					result = XYZ_to_REC709 * XYZ;
				break;
			case ColorSpace_REC2020:
					result = XYZ_to_REC2020 * XYZ;
				break;
			case ColorSpace_AP1:
			default:
					// Unreachable code
				break;
		}
	}

	return result;
}
