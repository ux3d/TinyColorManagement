#include "ImageDataModify.h"

bool fill(ImageData& imageData, const glm::vec4& color)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return color;
	});
}

bool gradeHorizontal(ImageData& imageData, const glm::vec4& start, const glm::vec4& end)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return glm::mix(start, end, fraction.s);
	});
}

bool gradeVertical(ImageData& imageData, const glm::vec4& start, const glm::vec4& end)
{
	return imageData.modify([&](const glm::vec4& c, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return glm::mix(start, end, fraction.t);
	});
}

bool multiply(ImageData& imageData, double factor)
{
	return imageData.modify([&](const glm::vec4& color, const glm::vec2& fraction, const glm::vec2& coordinate) {
		return color * glm::vec4(factor, factor, factor, 1.0);
	});
}
