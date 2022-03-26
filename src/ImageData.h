#ifndef IMAGEDATA_H_
#define IMAGEDATA_H_

#include <cstdint>
#include <functional>
#include <vector>

#include "ColorPrimaries.h"

class ImageData {

private:

	// Origin is bottom left.

	std::vector<float> pixels;
	uint32_t channels = 0;
	uint32_t width = 0;
	uint32_t height = 0;
	ColorSpace colorSpace;

public:

	ImageData(uint32_t channels, uint32_t width, uint32_t height, ColorSpace colorSpace = ColorSpace_SRGB);

	uint32_t getChannels() const;

	uint32_t getWidth() const;

	uint32_t getHeight() const;

	ColorSpace getColorSpace() const;

	const float* getPixelsData() const;

	bool isValid() const;

	//

	glm::vec4 getColor(uint32_t x, uint32_t y) const;

	bool setColor(uint32_t x, uint32_t y, const glm::vec4& color);

	//

	bool generateFill(const glm::vec4& color);

	bool generateGradeHorizontal(const glm::vec4& start, const glm::vec4& end);

	bool generateGradeVertical(const glm::vec4& start, const glm::vec4& end);

	bool generateChromacity(double Y);

	//

	bool modify(std::function<glm::vec4(const glm::vec4& color)> f);

	//

	bool gatherPixelDataSFLOAT(std::vector<float>& convertedPixels);

	bool gatherPixelDataUINT8(std::vector<uint8_t>& convertedPixels);

};

#endif /* IMAGEDATA_H_ */
