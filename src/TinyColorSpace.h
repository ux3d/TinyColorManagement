#ifndef TINYCOLORSPACE_H_
#define TINYCOLORSPACE_H_

#include <glm/glm.hpp>

// References
// ----------
//
// The Color Transformation Language
// https://github.com/ampas/CTL
//
// Academy Color Encoding System Developer Resources
// https://github.com/ampas/aces-dev
// https://github.com/ampas/aces-dev/blob/master/transforms/ctl/README-MATRIX.md
//
// Color Transformation Language User Guide and Reference Manual
// http://ampasctl.sourceforge.net/CtlManual.pdf
//
// Chromatic Adaptation
// http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html

//

struct Chromaticities
{
    glm::vec2	red;		// CIE xy coordinates of red primary
    glm::vec2	green;		// CIE xy coordinates of green primary
    glm::vec2	blue;		// CIE xy coordinates of blue primary
    glm::vec2	white;		// CIE xy coordinates of white point
};

const Chromaticities SRGB =
{
	  { 0.640,  0.330},
	  { 0.300,  0.600},
	  { 0.150,  0.060},
	  { 0.3127, 0.3290}		// D65
};

const Chromaticities REC709 = SRGB;

const Chromaticities REC2020 =
{
	  { 0.708, 0.292},
	  { 0.170, 0.797},
	  { 0.131, 0.046},
	  { 0.3127, 0.3290}		// D65
};

const Chromaticities AP0 =
{
	  { 0.73470,  0.26530},
	  { 0.00000,  1.00000},
	  { 0.00010, -0.07700},
	  { 0.32168,  0.33767}	// D60
};

const Chromaticities AP1 =
{
	  { 0.713,    0.293},
	  { 0.165,    0.830},
	  { 0.128,    0.044},
	  { 0.32168,  0.33767}	// D60
};

//

glm::vec3 XYZ_2_xyY(glm::vec3 XYZ);

glm::vec3 xyY_2_XYZ(glm::vec3 xyY);

//

glm::mat3 RGB_2_XYZ(const Chromaticities& chroma, double Y);

glm::mat3 XYZ_2_RGB(const Chromaticities& chroma, double Y);

//

glm::mat3 chromaticAdaptationMatrix(const glm::vec2& source, const glm::vec2& destination);

glm::mat3 saturationMatrix(double sat, glm::vec3 rgb2Y);

//

const glm::mat3 SRGB_2_XYZ = RGB_2_XYZ(SRGB, 1.0f);
const glm::mat3 XYZ_2_SRGB = XYZ_2_RGB(SRGB, 1.0f);

const glm::mat3 REC709_2_XYZ = RGB_2_XYZ(REC709, 1.0f);
const glm::mat3 XYZ_2_REC709 = XYZ_2_RGB(REC709, 1.0f);

const glm::mat3 REC2020_2_XYZ = RGB_2_XYZ(REC2020, 1.0f);
const glm::mat3 XYZ_2_REC2020 = XYZ_2_RGB(REC2020, 1.0f);

const glm::mat3 AP1_2_XYZ = RGB_2_XYZ(AP1, 1.0f);
const glm::mat3 XYZ_2_AP1 = XYZ_2_RGB(AP1, 1.0f);


const glm::mat3 D65_2_D60 = chromaticAdaptationMatrix(REC709.white, AP0.white);
const glm::mat3 D60_2_D65 = chromaticAdaptationMatrix(AP0.white, REC709.white);


const glm::vec3 AP1_RGB2Y = {
		AP1_2_XYZ[0][1],
        AP1_2_XYZ[1][1],
        AP1_2_XYZ[2][1]
};

const double RRT_SAT_FACTOR = 0.96;
const glm::mat3 RRT_SAT = saturationMatrix(RRT_SAT_FACTOR, AP1_RGB2Y);

const double ODT_SAT_FACTOR = 0.93;
const glm::mat3 ODT_SAT = saturationMatrix(ODT_SAT_FACTOR, AP1_RGB2Y);

//

glm::vec3 nlSRGB_2_SRGB_Fast(const glm::vec3& color);
glm::vec3 SRGB_2_nlSRGB_Fast(const glm::vec3& color);

glm::vec3 nlSRGB_2_SRGB(const glm::vec3& color);
glm::vec3 SRGB_2_nlSRGB(const glm::vec3& color);

glm::vec3 nlREC709_2_REC709(const glm::vec3& color);
glm::vec3 REC709_2_nlREC709(const glm::vec3& color);

glm::vec3 PQ_2_REC2020(const glm::vec3& color);
glm::vec3 REC2020_2_PQ(const glm::vec3& color);

#endif /* TINYCOLORSPACE_H_ */
