#include "imagefile.h"

#include "../objectinfo/universalobjectinterface.h"
#include "atlasfile.h"

namespace SpriterEngine
{

	ImageFile::ImageFile(std::string initialFilePath, point initialDefaultPivot) :
		File(initialFilePath),
		defaultPivot(initialDefaultPivot), atlasFile(0), atlasFrameData()
	{
	}

	ImageFile *ImageFile::imageFile()
	{
		return this;
	}

	void ImageFile::setAtlasFile(AtlasFile *initialAtlasFile, atlasframedata initialAtlasFrameData)
	{
		// TODO: if you override, call ImageFile::setAtlasFile(initialAtlasFile, initialAtlasFrameData) first
		atlasFile = initialAtlasFile;
		atlasFrameData = initialAtlasFrameData;
	}

	void ImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		if(atlasFile) {
			atlasFile->renderSprite(spriteInfo, atlasFrameData);
		}
		// TODO: override and add custom rendering code here using:

		// spriteInfo->getAlpha()
		// spriteInfo->getPosition()
		// spriteInfo->getAngle()
		// spriteInfo->getScale()
		// spriteInfo->getPivot()
	}

}
