#include "ImageData.h"

#include <string>

#include "CIE_XYZ_cmf.h"
#include "TransferFunctions.h"

ImageData::ImageData(uint32_t channels, uint32_t width, uint32_t height, ColorSpace colorSpace) :
	channels(channels), width(width), height(height), colorSpace(colorSpace)
{
	if (!isValid())
	{
		this->channels = 0;
		this->width = 0;
		this->height = 0;
		this->colorSpace = ColorSpace_UNKNOWN;
	}

	this->pixels.resize(channels * width * height);
}

uint32_t ImageData::getChannels() const
{
	return channels;
}

uint32_t ImageData::getWidth() const
{
	return width;
}

uint32_t ImageData::getHeight() const
{
	return height;
}

ColorSpace ImageData::getColorSpace() const
{
	return colorSpace;
}

const float* ImageData::getPixelsData() const
{
	return (const float*)pixels.data();
}

bool ImageData::isValid() const
{
	if (channels < 1 || channels > 4)
	{
		return false;
	}
	// For convenience, only support a specific dimension
	if (width < 16 || width > 16384)
	{
		return false;
	}
	if (height < 16 || height > 16384)
	{
		return false;
	}
	if (colorSpace == ColorSpace_UNKNOWN || colorSpace == ColorSpace_AP0)
	{
		return false;
	}

	return true;
}

glm::vec4 ImageData::getColor(uint32_t x, uint32_t y) const
{
	glm::vec4 result = glm::vec4(0.0, 0.0, 0.0, 0.0);

	if (x >= width || y >= height)
	{
		return result;
	}

	for (uint32_t c = 0; c < channels; c++)
	{
		result[c] = pixels[channels * width * (height - 1 - y) + channels * x + c];
	}

	return result;
}

bool ImageData::setColor(uint32_t x, uint32_t y, const glm::vec4& color)
{
	if (!isValid())
	{
		return false;
	}

	if (x >= width || y >= height)
	{
		return false;
	}

	for (uint32_t c = 0; c < channels; c++)
	{
		pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
	}

	return true;
}

bool ImageData::fill(const glm::vec4& color)
{
	if (!isValid())
	{
		return false;
	}

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
			}
		}
	}

	return false;
}

bool ImageData::multiply(const glm::vec4& color)
{
	if (!isValid())
	{
		return false;
	}

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] *= color[c];
			}
		}
	}

	return true;
}

bool ImageData::gradeHorizontal(const glm::vec4& start, const glm::vec4& end)
{
	if (!isValid())
	{
		return false;
	}

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			double weight = (double)x / (double)(width - 1);

			glm::vec4 gradient = glm::mix(start, end, weight);

			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = gradient[c];
			}
		}
	}

	return true;
}

bool ImageData::gradeVertical(const glm::vec4& start, const glm::vec4& end)
{
	if (!isValid())
	{
		return false;
	}

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			double weight = (double)y / (double)(height - 1);

			glm::vec4 gradient = glm::mix(start, end, weight);

			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = gradient[c];
			}
		}
	}

	return true;
}

bool ImageData::chromacity(const Chromaticities& chroma, double Y)
{
	if (!isValid())
	{
		return false;
	}

	std::vector<glm::vec3> xyYs;

	for (size_t i = 0; i < cmf1931.size(); i++)
	{
		glm::vec3 XYZ = cmf1931[i].XYZ;
		glm::vec3 xyY = XYZ_2_xyY(XYZ);

		xyYs.push_back(xyY);
	}

	double slope = (xyYs.back().y - xyYs.front().y) / (xyYs.back().x - xyYs.front().x);

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			double xC = (double)x / (double)(width - 1);
			double yC = (double)y / (double)(height - 1);

			glm::vec3 color = glm::vec3(0.0, 0.0, 0.0);

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
				switch (colorSpace)
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

				color = RGB;
			}

			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
			}
		}
	}

	return true;
}

//

bool ImageData::gatherPixelDataSFLOAT(std::vector<float>& convertedPixels)
{
	if (!isValid())
	{
		return false;
	}

	convertedPixels.reserve(channels * width * height);

	memcpy(convertedPixels.data(), pixels.data(), sizeof(float) * channels * width * height);

	return true;
}

bool ImageData::gatherPixelDataUINT8(std::vector<uint8_t>& convertedPixels)
{
	if (!isValid())
	{
		return false;
	}

	convertedPixels.reserve(channels * width * height);

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			for (uint32_t c = 0; c < channels; c++)
			{
				double channel = pixels[channels * width * (height - 1 - y) + channels * x + c];
				channel = glm::clamp(channel * 255.0, 0.0, 255.0);
				convertedPixels[channels * width * (height - 1 - y) + channels * x + c] = (uint8_t)channel;
			}
		}
	}

	return true;
}
