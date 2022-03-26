#include "Luminance.h"

double SRGB_2_Y(const glm::vec3& color)
{
	return SRGB_2_Yrgb[0] * color.r + SRGB_2_Yrgb[1] * color.g + SRGB_2_Yrgb[2] * color.b;
}

double REC709_2_Y(const glm::vec3& color)
{
	return REC709_2_Yrgb[0] * color.r + REC709_2_Yrgb[1] * color.g + REC709_2_Yrgb[2] * color.b;
}

double REC2020_2_Y(const glm::vec3& color)
{
	return REC2020_2_Yrgb[0] * color.r + REC2020_2_Yrgb[1] * color.g + REC2020_2_Yrgb[2] * color.b;
}

double AP1_2_Y(const glm::vec3& color)
{
	return AP1_2_Yrgb[0] * color.r + AP1_2_Yrgb[1] * color.g + AP1_2_Yrgb[2] * color.b;
}
