#include "TinyColorSpace.h"

#include <cstdio>
#include <string>

int main(int argc, char* argv[])
{
	glm::mat3 test = glm::mat3(1.0);

	//

	test = XYZ_2_AP1 * D65_2_D60 * SRGB_2_XYZ;
	printMat3(test);

	printMat3(RRT_SAT);

	test = RRT_SAT * test;
	printMat3(test);

	printf("---\n\n");

	//

	test = XYZ_2_SRGB * D60_2_D65 * AP1_2_XYZ;
	printMat3(test);

	printMat3(ODT_SAT);

	test = test * ODT_SAT;
	printMat3(test);

	printf("---\n\n");

	//
	//
	//

	ImageData imageData(3, 512, 512);

	chromacity(imageData, 1.0);

	//

	std::string filename;

	filename = "test.exr";
	if (!save(imageData, filename))
	{
		return -1;
	}
	printf("Saved '%s'\n", filename.c_str());

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
