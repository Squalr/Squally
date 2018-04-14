#include "atlasfile.h"

#include "../objectinfo/universalobjectinterface.h"

namespace SpriterEngine
{

	AtlasFile::AtlasFile(std::string initialFilePath) :
		File(initialFilePath)
	{
	}

	AtlasFile *AtlasFile::atlasFile()
	{
		return this;
	}

	void AtlasFile::renderSprite(SpriterEngine::UniversalObjectInterface *spriteInfo, const atlasframedata data)
	{
		// TODO: override and add custom rendering code here using:

		// spriteInfo->getAlpha()
		// spriteInfo->getPosition()
		// spriteInfo->getAngle()
		// spriteInfo->getScale()
		// spriteInfo->getPivot()
	}

}
