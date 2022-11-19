#ifndef TRANSFERFUNCTIONS_H_
#define TRANSFERFUNCTIONS_H_

#include <glm/glm.hpp>

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_CONVERSION
// see https://github.com/ampas/aces-dev/blob/master/transforms/ctl/README-MATRIX.md
//
// nl_ prefix is the non-linear representation

glm::vec3 nl_sRGB_to_sRGB_Fast(const glm::vec3& color);
glm::vec3 sRGB_to_nl_sRGB_Fast(const glm::vec3& color);

glm::vec3 nl_sRGB_to_sRGB(const glm::vec3& color);
glm::vec3 sRGB_to_nl_SRGB(const glm::vec3& color);

glm::vec3 nl_REC709_to_REC709(const glm::vec3& color);
glm::vec3 REC709_to_nl_REC709(const glm::vec3& color);

glm::vec3 PQ_to_REC2020(const glm::vec3& color);
glm::vec3 REC2020_to_PQ(const glm::vec3& color);

glm::vec3 HLG_to_REC2020(const glm::vec3& color);
glm::vec3 REC2020_to_HLG(const glm::vec3& color);

#endif /* TRANSFERFUNCTIONS_H_ */
