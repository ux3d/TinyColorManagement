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
	ColorSpace colorSpace = ColorSpace_UNKNOWN;

public:

	ImageData();
	ImageData(uint32_t channels, uint32_t width, uint32_t height, ColorSpace colorSpace = ColorSpace_sRGB);

	bool reformat(uint32_t channels, uint32_t width, uint32_t height, ColorSpace colorSpace, const std::vector<float>& pixelData);

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

	bool modify(std::function<glm::vec4(const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate)> f);

};

#endif /* IMAGEDATA_H_ */
