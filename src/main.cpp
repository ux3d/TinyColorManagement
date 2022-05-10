#include "TinyColorSpace.h"

#include <cstdio>
#include <string>

int main(int argc, char* argv[])
{
	//
	// Printing out matrices for usage in shader code.
	//

	glm::mat3 test = glm::mat3(1.0);

	// From SRGB to AP1 color space
	test = XYZ_2_AP1 * D65_2_D60 * SRGB_2_XYZ;
	printMat3(test);

	// Approximated ACES tone mapping from Stephen Hill

	printMat3(RRT_SAT);

	test = RRT_SAT * test;
	printMat3(test);

	printMat3(ODT_SAT);

	// From AP1 to SRGB color space
	test = XYZ_2_SRGB * D60_2_D65 * AP1_2_XYZ;
	printMat3(test);

	test = test * ODT_SAT;
	printMat3(test);

	printf("---\n\n");

	//
	// Generating a color gamut.
	//

	ImageData imageData(4, 512, 512);

	chromacity(imageData, 1.0);

	// Saving and loading of different file formats.

	std::string filename;

	filename = "test.exr";
	if (!save(imageData, filename))
	{
		return -1;
	}
	printf("Saved '%s'\n", filename.c_str());

	// Convert from linear to non-linear space.
	imageData.modify([&](const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return glm::vec4(SRGB_2_nlSRGB(glm::vec3(color)), color.a);
	});

	filename = "test.png";
	if (!save(imageData, filename))
	{
		return -1;
	}
	printf("Saved '%s'\n", filename.c_str());

	//

	ImageData loadData;
	if (!load(loadData, filename))
	{
		return -1;
	}
	printf("Loaded '%s'\n", filename.c_str());

	filename = "test_out.png";
	if (!save(loadData, filename))
	{
		return -1;
	}
	printf("Saved '%s'\n", filename.c_str());

	return 0;
}
