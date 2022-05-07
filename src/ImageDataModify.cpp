#include "ImageDataModify.h"

#include "CIE_XYZ_cmf.h"

bool fill(ImageData& imageData, const glm::vec4& color)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return color;
	});
}

bool gradeHorizontal(ImageData& imageData, const glm::vec4& start, const glm::vec4& end)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return glm::mix(start, end, fraction.s);
	});
}

bool gradeVertical(ImageData& imageData, const glm::vec4& start, const glm::vec4& end)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return glm::mix(start, end, fraction.t);
	});
}

bool multiply(ImageData& imageData, double factor)
{
	return imageData.modify([&](const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return color * glm::vec4(factor, factor, factor, 1.0);
	});
}

bool chromacity(ImageData& imageData, double Y)
{
	std::vector<glm::vec3> xyYs;

	for (size_t i = 0; i < cmf1931.size(); i++)
	{
		glm::vec3 XYZ = cmf1931[i].XYZ;
		glm::vec3 xyY = XYZ_2_xyY(XYZ);

		xyYs.push_back(xyY);
	}

	double slope = (xyYs.back().y - xyYs.front().y) / (xyYs.back().x - xyYs.front().x);

	return imageData.modify([&](const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate) {
		double xC = fraction.x;
		double yC = fraction.y;

		bool bottomLeft = false;
		bool bottomRight = false;
		bool topLeft = false;
		bool topRight = false;
		for (size_t i = 0; i < xyYs.size(); i++)
		{
			if (xC >= xyYs[i].x && yC >= xyYs[i].y)
			{
				bottomLeft = true;
			}
			if (xC >= xyYs[i].x && yC <= xyYs[i].y)
			{
				topLeft = true;
			}
			if (xC <= xyYs[i].x && yC <= xyYs[i].y)
			{
				topRight = true;
			}

			//

			if (yC >= slope * (xC - xyYs.front().x) + xyYs.front().y)
			{
				bottomRight = true;
			}
		}

		if (bottomLeft && bottomRight && topLeft && topRight)
		{
			glm::vec3 XYZ = xyY_2_XYZ(glm::vec3(xC, yC, Y));

			glm::vec3 RGB;
			switch (imageData.getColorSpace())
			{
				case ColorSpace_SRGB:
						RGB = XYZ_2_SRGB * XYZ;
					break;
				case ColorSpace_REC709:
						RGB = XYZ_2_REC709 * XYZ;
					break;
				case ColorSpace_REC2020:
						RGB = XYZ_2_REC2020 * XYZ;
					break;
				case ColorSpace_AP1:
						RGB = XYZ_2_AP1 * XYZ;
					break;
				default:
						// Unreachable code
					break;
			}

			// Make sure, one channel is fully saturated.
			RGB /= glm::max(glm::max(RGB.r, RGB.g), RGB.b);

			return glm::vec4(RGB, 1.0);
		}

		return glm::vec4(0.0, 0.0, 0.0, 1.0);
	});
}
