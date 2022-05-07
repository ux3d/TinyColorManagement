#include <cstdio>
#include <string>
#include <vector>


#include "TinyColorSpace.h"

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

	imageData.generateFill(glm::vec4(0.0, 0.8, 0.0, 1.0));
	//imageData.generateGradeHorizontal(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 0.0));
	//imageData.generateGradeVertical(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(1.0, 1.0, 1.0, 0.0));
	//imageData.generateChromacity(1.0);

	/*
	// Fill with color
	glm::vec4 yellowColor = glm::vec4(1.0, 1.0, 0.0, 1.0);
	imageData.modify([&](const glm::vec4& color, const glm::vec2& percent, const glm::vec2& coordinate) {
		return yellowColor;
	});
	*/

	/*
	// Multiply color with given factor
	double factor = 0.5;
	imageData.modify([&](const glm::vec4& color, const glm::vec2& percent, const glm::vec2& coordinate) {
		return color * glm::vec4(factor, factor, factor, 1.0);
	});
	*/

	// Tonemap
	/*imageData.modify([&](const glm::vec4& color, const glm::vec2& percent, const glm::vec2& coordinate) {
		return glm::vec4(tonemapReinhard(color), color.a);
	});*/

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

	glm::vec4 color = loadData.getColor(0, 0);
	printf("%f %f %f %f\n", color.r, color.g, color.b, color.a);

	filename = "test_out.png";
	if (!save(loadData, filename))
	{
		return -1;
	}
	printf("Saved '%s'\n", filename.c_str());

	//

	// Sunny 16 rule with a 50mm lense see https://en.wikipedia.org/wiki/Sunny_16_rule

	double lense = 50.0;
	double ev100 = calculateEV100(lense / 16.0, 1.0 / 100.0, 100.0);
	printf("Exposure: %f\n", EV100_2_EXPOSURE(ev100));

	return 0;
}
