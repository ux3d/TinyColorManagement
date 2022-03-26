#include "ImageData.h"

#include "CIE_XYZ_cmf.h"
#include "TransferFunctions.h"

ImageData::ImageData(uint32_t channels, uint32_t width, uint32_t height)
{
	if (channels < 1 || channels > 4)
	{
		return;
	}
	// Only support 8K today
	if (width < 1 || width > 7680)
	{
		return;
	}
	if (height < 1 || height > 4320)
	{
		return;
	}

	//

	this->pixels.resize(channels * width * height);
	this->channels = channels;
	this->width = width;
	this->height = height;
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

const float* ImageData::getPixelsData() const
{
	return (const float*)pixels.data();
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

void ImageData::setColor(uint32_t x, uint32_t y, const glm::vec4& color)
{
	if (x >= width || y >= height)
	{
		return;
	}

	for (uint32_t c = 0; c < channels; c++)
	{
		pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
	}
}

void ImageData::fill(const glm::vec4& color)
{
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
}

void ImageData::multiply(const glm::vec4& color)
{
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
}

void ImageData::gradeHorizontal(const glm::vec4& start, const glm::vec4& end)
{
	if (width <= 1)
	{
		return;
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
}

void ImageData::gradeVertical(const glm::vec4& start, const glm::vec4& end)
{
	if (height <= 1)
	{
		return;
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
}

void ImageData::chromacity(const Chromaticities& chroma, double Y)
{
	if (width <= 1 || height <= 1 || channels < 3)
	{
		return;
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

				glm::vec3 SRGB = XYZ_2_SRGB * XYZ;

				// Make sure, one channel is fully saturated.
				SRGB /= glm::max(glm::max(SRGB.r, SRGB.g), SRGB.b);

				color = SRGB;
			}

			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
			}
		}
	}
}

//

void ImageData::convertToUINT8(std::vector<uint8_t>& convertedPixels)
{
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
}
