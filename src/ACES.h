#ifndef ACES_H_
#define ACES_H_

#include "Luminance.h"

glm::mat3 saturationMatrix(double sat, glm::vec3 Yrgb);

const double RRT_SAT_FACTOR = 0.96;
const glm::mat3 RRT_SAT = saturationMatrix(RRT_SAT_FACTOR, AP1_2_Yrgb);

const double ODT_SAT_FACTOR = 0.93;
const glm::mat3 ODT_SAT = saturationMatrix(ODT_SAT_FACTOR, AP1_2_Yrgb);

#endif /* ACES_H_ */
