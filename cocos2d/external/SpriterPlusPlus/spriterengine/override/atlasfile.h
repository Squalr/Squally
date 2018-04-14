#ifndef ATLASFILE_H
#define ATLASFILE_H

#include <string>

#include "../file/file.h"

#include "../global/global.h"
#include "../global/atlas.h"

namespace SpriterEngine
{
	class UniversalObjectInterface;
	class AtlasFile;

	class AtlasFile : public File
	{
	public:
		AtlasFile(std::string initialFilePath);

		AtlasFile *atlasFile() override;

		virtual void renderSprite(UniversalObjectInterface *spriteInfo, const atlasframedata data);
	};

}

#endif // ATLASFILE_H
