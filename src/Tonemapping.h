#ifndef TONEMAPPING_H_
#define TONEMAPPING_H_

#include "ColorPrimaries.h"

// see https://64.github.io/tonemapping/

glm::vec3 tonemapNone(const glm::vec3& color);

glm::vec3 tonemapReinhard(const glm::vec3& color);

glm::vec3 tonemapAces(const glm::vec3& color, ColorSpace colorSpace = ColorSpace_SRGB);

#endif /* TONEMAPPING_H_ */
