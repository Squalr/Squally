#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>

#include "../file/file.h"

#include "../global/global.h"
#include "../global/atlas.h"

namespace SpriterEngine
{
	class UniversalObjectInterface;
	class AtlasFile;

	class ImageFile : public File
	{
	public:
		ImageFile(std::string initialFilePath, point initialDefaultPivot);

		ImageFile *imageFile() override;

		virtual void setAtlasFile(AtlasFile* initialAtlasFile, atlasframedata initialAtlasFrameData);

		point defaultPivot;

		virtual void renderSprite(UniversalObjectInterface *spriteInfo);

	protected:
		AtlasFile* atlasFile;
		atlasframedata atlasFrameData;
	};

}

#endif // IMAGEFILE_H
