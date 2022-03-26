#include "ImageDataIO.h"

#include <filesystem>

#include <OpenImageIO/imageio.h>

using namespace OIIO;

bool save(const ImageData& imageData, const std::string& filename)
{
	if (!imageData.isValid())
	{
		return false;
	}

	std::filesystem::path filesystemPath(filename);
	std::string extension = filesystemPath.extension().generic_string();

	TypeDesc format;
	if (extension == ".hdr" || extension == ".exr")
	{
		format = TypeDesc::FLOAT;
	}
	else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
	{
		format = TypeDesc::UINT8;
	}
	else
	{
		return false;
	}

	std::unique_ptr<ImageOutput> imageOutput = ImageOutput::create(filename);
	if (!imageOutput)
	{
		return false;
	}

	ImageSpec imageSpec(imageData.getWidth(), imageData.getHeight(), imageData.getChannels(), format);
	if (!imageOutput->open(filename, imageSpec))
	{
		return false;
	}

	if (!imageOutput->write_image(TypeDesc::FLOAT, imageData.getPixelsData()))
	{
		return false;
	}

	return imageOutput->close();
}
