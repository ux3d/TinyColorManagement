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

	auto imageOutput = ImageOutput::create(filename);
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

bool load(ImageData& imageData, const std::string& filename)
{
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

	auto imageInput = ImageInput::open(filename);
	if (!imageInput)
	{
		return false;
	}

	ImageSpec imageSpec = imageInput->spec();
	imageSpec.format.basetype = TypeDesc::FLOAT;

	std::vector<float> pixelData(sizeof(float) * imageSpec.nchannels * imageSpec.width * imageSpec.height);
	if (!imageInput->read_image(imageSpec.format, pixelData.data()))
	{
		return false;
	}

	if (!imageInput->close())
	{
		return false;
	}

	return imageData.reformat(imageSpec.nchannels, imageSpec.width, imageSpec.height, ColorSpace_sRGB, pixelData);
}
