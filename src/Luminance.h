#ifndef LUMINANCE_H_
#define LUMINANCE_H_

#include "ColorPrimaries.h"

const glm::vec3 SRGB_2_Yrgb = {
	SRGB_2_XYZ[0][1],
	SRGB_2_XYZ[1][1],
	SRGB_2_XYZ[2][1]
};

const glm::vec3 REC709_2_Yrgb = {
	REC709_2_XYZ[0][1],
	REC709_2_XYZ[1][1],
	REC709_2_XYZ[2][1]
};

const glm::vec3 REC2020_2_Yrgb = {
	REC2020_2_XYZ[0][1],
	REC2020_2_XYZ[1][1],
	REC2020_2_XYZ[2][1]
};

const glm::vec3 AP1_2_Yrgb = {
	AP1_2_XYZ[0][1],
	AP1_2_XYZ[1][1],
	AP1_2_XYZ[2][1]
};

double SRGB_2_Y(const glm::vec3& color);

double REC709_2_Y(const glm::vec3& color);

double REC2020_2_Y(const glm::vec3& color);

double AP1_2_Y(const glm::vec3& color);

#endif /* LUMINANCE_H_ */
