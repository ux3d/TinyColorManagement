#ifndef LUMINANCE_H_
#define LUMINANCE_H_

#include "ColorPrimaries.h"

const glm::vec3 sRGB_to_Yrgb = {
	sRGB_to_XYZ[0][1],
	sRGB_to_XYZ[1][1],
	sRGB_to_XYZ[2][1]
};

const glm::vec3 REC709_to_Yrgb = {
	REC709_to_XYZ[0][1],
	REC709_to_XYZ[1][1],
	REC709_to_XYZ[2][1]
};

const glm::vec3 REC2020_to_Yrgb = {
	REC2020_to_XYZ[0][1],
	REC2020_to_XYZ[1][1],
	REC2020_to_XYZ[2][1]
};

const glm::vec3 AP1_to_Yrgb = {
	AP1_to_XYZ[0][1],
	AP1_to_XYZ[1][1],
	AP1_to_XYZ[2][1]
};

double sRGB_to_Y(const glm::vec3& color);

double REC709_to_Y(const glm::vec3& color);

double REC2020_to_Y(const glm::vec3& color);

double AP1_to_Y(const glm::vec3& color);

#endif /* LUMINANCE_H_ */
