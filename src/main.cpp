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

	/*const char* filename = "test.exr";
	std::unique_ptr<ImageOutput> output = ImageOutput::create(filename);
	if (!output)
	{
		return -1;
	}
	ImageSpec spec (imageData.getWidth(), imageData.getHeight(), imageData.getChannels(), TypeDesc::FLOAT);
	output->open(filename, spec);
	output->write_image(TypeDesc::FLOAT, imageData.getPixelsData());
	output->close();*/

	std::vector<uint8_t> pixelData;
	imageData.convertToUINT8(pixelData);

	const char* filename = "test.png";
	std::unique_ptr<ImageOutput> output = ImageOutput::create(filename);
	if (!output)
	{
		return -1;
	}
	ImageSpec spec (imageData.getWidth(), imageData.getHeight(), imageData.getChannels(), TypeDesc::UINT8);
	output->open(filename, spec);
	output->write_image(TypeDesc::UINT8, pixelData.data());
	output->close();

	printf("Saved '%s'\n", filename);

	return 0;
}
