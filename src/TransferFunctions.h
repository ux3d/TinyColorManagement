#ifndef TRANSFERFUNCTIONS_H_
#define TRANSFERFUNCTIONS_H_

#include <glm/glm.hpp>

// see https://www.khronos.org/registry/DataFormat/specs/1.3/dataformat.1.3.html#TRANSFER_CONVERSION

glm::vec3 nlSRGB_2_SRGB_Fast(const glm::vec3& color);
glm::vec3 SRGB_2_nlSRGB_Fast(const glm::vec3& color);

glm::vec3 nlSRGB_2_SRGB(const glm::vec3& color);
glm::vec3 SRGB_2_nlSRGB(const glm::vec3& color);

glm::vec3 nlREC709_2_REC709(const glm::vec3& color);
glm::vec3 REC709_2_nlREC709(const glm::vec3& color);

glm::vec3 PQ_2_REC2020(const glm::vec3& color);
glm::vec3 REC2020_2_PQ(const glm::vec3& color);

glm::vec3 HLG_2_REC2020(const glm::vec3& color);
glm::vec3 REC2020_2_HLG(const glm::vec3& color);

#endif /* TRANSFERFUNCTIONS_H_ */
