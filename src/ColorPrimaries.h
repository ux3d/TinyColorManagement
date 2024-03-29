#ifndef COLORPRIMARIES_H_
#define COLORPRIMARIES_H_

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
// Conversion
// http://www.brucelindbloom.com/index.html

// Illuminant
const glm::vec2 D65 = { 0.3127,  0.3290};
const glm::vec2 D60 = { 0.32168, 0.33767};

enum ColorSpace {
	ColorSpace_UNKNOWN,
	ColorSpace_sRGB,
	ColorSpace_REC709,
	ColorSpace_REC2020,
	ColorSpace_AP0,
	ColorSpace_AP1
};

struct Chromaticities
{
    glm::vec2	red;		// CIE xy coordinates of red primary
    glm::vec2	green;		// CIE xy coordinates of green primary
    glm::vec2	blue;		// CIE xy coordinates of blue primary
    glm::vec2	white;		// CIE xy coordinates of white point
    //
    ColorSpace colorSpace;
};

const Chromaticities sRGB =
{
	  { 0.640,  0.330},
	  { 0.300,  0.600},
	  { 0.150,  0.060},
	  D65,
	  ColorSpace_sRGB
};

const Chromaticities REC709 =
{
	  { 0.640,  0.330},
	  { 0.300,  0.600},
	  { 0.150,  0.060},
	  D65,
	  ColorSpace_REC709			// equal to SRGB
};

const Chromaticities REC2020 =
{
	  { 0.708, 0.292},
	  { 0.170, 0.797},
	  { 0.131, 0.046},
	  D65,
	  ColorSpace_REC2020
};

const Chromaticities AP0 =
{
	  { 0.73470,  0.26530},
	  { 0.00000,  1.00000},
	  { 0.00010, -0.07700},
	  D60,
	  ColorSpace_AP0
};

const Chromaticities AP1 =
{
	  { 0.713,    0.293},
	  { 0.165,    0.830},
	  { 0.128,    0.044},
	  D60,
	  ColorSpace_AP1
};

//

glm::vec3 XYZ_to_xyY(glm::vec3 XYZ);

glm::vec3 xyY_to_XYZ(glm::vec3 xyY);

//

glm::mat3 RGB_to_XYZ(const Chromaticities& chroma, double Y);

glm::mat3 XYZ_to_RGB(const Chromaticities& chroma, double Y);

//

const glm::mat3 sRGB_to_XYZ = RGB_to_XYZ(sRGB, 1.0f);
const glm::mat3 XYZ_to_sRGB = XYZ_to_RGB(sRGB, 1.0f);

const glm::mat3 REC709_to_XYZ = RGB_to_XYZ(REC709, 1.0f);
const glm::mat3 XYZ_to_REC709 = XYZ_to_RGB(REC709, 1.0f);

const glm::mat3 REC2020_to_XYZ = RGB_to_XYZ(REC2020, 1.0f);
const glm::mat3 XYZ_to_REC2020 = XYZ_to_RGB(REC2020, 1.0f);

const glm::mat3 AP0_to_XYZ = RGB_to_XYZ(AP0, 1.0f);
const glm::mat3 XYZ_to_AP0 = XYZ_to_RGB(AP0, 1.0f);

const glm::mat3 AP1_to_XYZ = RGB_to_XYZ(AP1, 1.0f);
const glm::mat3 XYZ_to_AP1 = XYZ_to_RGB(AP1, 1.0f);

//

glm::mat3 chromaticAdaptationMatrix(const glm::vec2& source, const glm::vec2& destination);

const glm::mat3 D65_to_D60 = chromaticAdaptationMatrix(D65, D60);
const glm::mat3 D60_to_D65 = chromaticAdaptationMatrix(D60, D65);

#endif /* COLORPRIMARIES_H_ */
