#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <string>

#include "../global/global.h"
#include "../global/atlas.h"

namespace SpriterEngine
{

	class ImageFile;
	class SoundFile;
	class AtlasFile;
	class SpriterFileDocumentWrapper;

	class FileFactory
	{
	public:
		FileFactory();
		virtual ~FileFactory();

		virtual ImageFile *newImageFile(const std::string &initialFilePath, point initialDefaultPivot, atlasdata atlasData);
		virtual SoundFile *newSoundFile(const std::string &initialFilePath);
		virtual AtlasFile *newAtlasFile(const std::string &initialFilePath);

		virtual SpriterFileDocumentWrapper *newScmlDocumentWrapper();
		virtual SpriterFileDocumentWrapper *newSconDocumentWrapper();
	};

}

#endif // FILEFACTORY_H
