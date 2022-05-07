#include "ImageData.h"

#include <string>

#include "CIE_XYZ_cmf.h"
#include "TransferFunctions.h"

ImageData::ImageData()
{
}

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

bool ImageData::reformat(uint32_t channels, uint32_t width, uint32_t height, ColorSpace colorSpace, const std::vector<float>& pixelData)
{
	this->channels = channels;
	this->width = width;
	this->height = height;
	this->colorSpace = colorSpace;

	if (!isValid())
	{
		this->channels = 0;
		this->width = 0;
		this->height = 0;
		this->colorSpace = ColorSpace_UNKNOWN;

		return false;
	}

	this->pixels.resize(channels * width * height);

	memcpy(this->pixels.data(), pixelData.data(), sizeof(float) * channels * width * height);

	return true;
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
	glm::vec4 result = glm::vec4(0.0, 0.0, 0.0, 1.0);

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

//

bool ImageData::modify(std::function<glm::vec4(const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate)> f)
{
	if (!isValid())
	{
		return false;
	}

	double xStep = 1.0 / (width + 1);
	double yStep = 1.0 / (height + 1);

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			glm::vec4 color = glm::vec4(0.0, 0.0, 0.0, 1.0);

			for (uint32_t c = 0; c < channels; c++)
			{
				color[c] = pixels[channels * width * (height - 1 - y) + channels * x + c];
			}

			color = f(color, glm::vec2((double)x/(double)(width - 1), (double)y/(double)(height - 1)), glm::vec2((double)(x + 1) * xStep, (double)(y + 1) * yStep));

			for (uint32_t c = 0; c < channels; c++)
			{
				pixels[channels * width * (height - 1 - y) + channels * x + c] = color[c];
			}
		}
	}

	return true;
}
