#ifndef ACES_H_
#define ACES_H_

#include "ColorPrimaries.h"

glm::mat3 saturationMatrix(double sat, glm::vec3 rgb2Y);

const glm::vec3 AP1_RGB2Y = {
		AP1_2_XYZ[0][1],
        AP1_2_XYZ[1][1],
        AP1_2_XYZ[2][1]
};

const double RRT_SAT_FACTOR = 0.96;
const glm::mat3 RRT_SAT = saturationMatrix(RRT_SAT_FACTOR, AP1_RGB2Y);

const double ODT_SAT_FACTOR = 0.93;
const glm::mat3 ODT_SAT = saturationMatrix(ODT_SAT_FACTOR, AP1_RGB2Y);

#endif /* ACES_H_ */
