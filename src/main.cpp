#include <cstdio>
#include <string>
#include <vector>

#include <OpenImageIO/imageio.h>

#include "TinyColorSpace.h"

using namespace OIIO;

//

void generateMat3(const glm::mat3& m)
{
	printf("const mat3 m = mat3(\n");
	for (size_t r = 0; r < 3; r++)
	{
		std::string comment;

		printf("   ");
		for (size_t c = 0; c < 3; c++)
		{
			if (m[r][c] >= 0.0)
			{
				printf(" ");
			}
			printf("%f", m[r][c]);
			if (m[c][r] >= 0.0)
			{
				comment += " ";
			}
			comment += std::to_string(m[c][r]);
			if (c != 2 || r != 2)
			{
				printf(", ");
				comment += ", ";
			}
			else
			{
				printf("  ");
			}
		}
		printf("   // %s", comment.c_str());
		printf("\n");
	}
	printf(");\n\n");
}

//

class ImageData {

private:

	// Origin is bottom left.

	std::vector<float> pixels;
	uint32_t channels = 0;
	uint32_t width = 0;
	uint32_t height = 0;

public:

	ImageData(uint32_t channels, uint32_t width, uint32_t height)
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

	uint32_t getChannels() const
	{
		return channels;
	}

	uint32_t getWidth() const
	{
		return width;
	}

	uint32_t getHeight() const
	{
		return height;
	}

	const float* getPixelsData() const
	{
		return (const float*)pixels.data();
	}

	//

	glm::vec4 getColor(uint32_t x, uint32_t y)
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

	void setColor(uint32_t x, uint32_t y, const glm::vec4& color)
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

	void fill(const glm::vec4& color)
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

	void multiply(const glm::vec4& color)
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

	void gradeHorizontal(const glm::vec4& start, const glm::vec4& end)
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

	void gradeVertical(const glm::vec4& start, const glm::vec4& end)
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

	void chromacity(const Chromaticities& chroma, double Y)
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

};

//

int main(int argc, char* argv[])
{
	glm::mat3 test = glm::mat3(1.0);

	//

	test = XYZ_2_AP1 * D65_2_D60 * SRGB_2_XYZ;
	generateMat3(test);

	generateMat3(RRT_SAT);

	test = RRT_SAT * test;
	generateMat3(test);

	printf("---\n\n");

	//

	test = XYZ_2_SRGB * D60_2_D65 * AP1_2_XYZ;
	generateMat3(test);

	generateMat3(ODT_SAT);

	test = test * ODT_SAT;
	generateMat3(test);

	//
	//
	//

	ImageData imageData(3, 512, 512);
	//imageData.fill(glm::vec4(1.0, 0.0, 0.0, 0.0));
	//imageData.gradeHorizontal(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 0.0));
	//imageData.gradeVertical(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 0.0));
	imageData.chromacity(SRGB, 1.0);

	//

	const char* filename = "test.exr";
	std::unique_ptr<ImageOutput> output = ImageOutput::create(filename);
	if (!output)
	{
		return -1;
	}
	ImageSpec spec (imageData.getWidth(), imageData.getHeight(), imageData.getChannels(), TypeDesc::FLOAT);
	output->open(filename, spec);
	output->write_image(TypeDesc::FLOAT, imageData.getPixelsData());
	output->close();

	printf("Saved '%s'\n", filename);

	return 0;
}
