#ifndef IMAGEDATAMODIFY_H_
#define IMAGEDATAMODIFY_H_

#include "ImageData.h"

bool fill(ImageData& imageData, const glm::vec4& color);

bool gradeHorizontal(ImageData& imageData, const glm::vec4& start, const glm::vec4& end);

bool gradeVertical(ImageData& imageData, const glm::vec4& start, const glm::vec4& end);

bool multiply(ImageData& imageData, double factor);

bool chromacity(ImageData& imageData, double Y);

#endif /* IMAGEDATAMODIFY_H_ */
