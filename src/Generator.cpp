#include "Generator.h"

#include <cstdio>

void printMat3(const glm::mat3& matrix, bool HLSL)
{
	glm::mat3 m = matrix;
	if (HLSL)
	{
		m = glm::transpose(m);
		printf("// HLSL\n");
	}
	else
	{
		printf("// GLSL\n");
	}

	printf("const mat3 m = mat3(\n");
	for (size_t r = 0; r < 3; r++)
	{
		printf("   ");
		for (size_t c = 0; c < 3; c++)
		{
			if (m[r][c] >= 0.0)
			{
				printf(" ");
			}
			printf("%f", m[r][c]);
			if (c != 2 || r != 2)
			{
				printf(", ");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	printf(");\n\n");
}
