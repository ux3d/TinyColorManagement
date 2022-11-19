#include "Luminance.h"

double sRGB_to_Y(const glm::vec3& color)
{
	return sRGB_to_Yrgb[0] * color.r + sRGB_to_Yrgb[1] * color.g + sRGB_to_Yrgb[2] * color.b;
}

double REC709_to_Y(const glm::vec3& color)
{
	return REC709_to_Yrgb[0] * color.r + REC709_to_Yrgb[1] * color.g + REC709_to_Yrgb[2] * color.b;
}

double REC2020_to_Y(const glm::vec3& color)
{
	return REC2020_to_Yrgb[0] * color.r + REC2020_to_Yrgb[1] * color.g + REC2020_to_Yrgb[2] * color.b;
}

double AP1_to_Y(const glm::vec3& color)
{
	return AP1_to_Yrgb[0] * color.r + AP1_to_Yrgb[1] * color.g + AP1_to_Yrgb[2] * color.b;
}
