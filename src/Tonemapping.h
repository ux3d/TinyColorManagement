#ifndef TONEMAPPING_H_
#define TONEMAPPING_H_

#include <glm/glm.hpp>

// see https://64.github.io/tonemapping/

enum ColorSpace {
	ColorSpace_SRGB,
	ColorSpace_REC709,
	ColorSpace_REC2020,
	ColorSpace_AP1
};

glm::vec3 tonemapNone(const glm::vec3& color);

glm::vec3 tonemapReinhard(const glm::vec3& color);

glm::vec3 tonemapAces(const glm::vec3& color, ColorSpace colorSpace = ColorSpace_SRGB);

#endif /* TONEMAPPING_H_ */
