#ifndef IMAGEDATA_H_
#define IMAGEDATA_H_

#include <cstdint>
#include <vector>

#include "ColorPrimaries.h"

// Data and calculations are to be expected in linear SRGB space.

class ImageData {

private:

	// Origin is bottom left.

	std::vector<float> pixels;
	uint32_t channels = 0;
	uint32_t width = 0;
	uint32_t height = 0;

public:

	ImageData(uint32_t channels, uint32_t width, uint32_t height);

	uint32_t getChannels() const;

	uint32_t getWidth() const;

	uint32_t getHeight() const;

	const float* getPixelsData() const;

	//

	glm::vec4 getColor(uint32_t x, uint32_t y) const;

	void setColor(uint32_t x, uint32_t y, const glm::vec4& color);

	void fill(const glm::vec4& color);

	void multiply(const glm::vec4& color);

	void gradeHorizontal(const glm::vec4& start, const glm::vec4& end);

	void gradeVertical(const glm::vec4& start, const glm::vec4& end);

	void chromacity(const Chromaticities& chroma, double Y);

	//

	void convertToUINT8(std::vector<uint8_t>& convertedPixels);

};

#endif /* IMAGEDATA_H_ */
