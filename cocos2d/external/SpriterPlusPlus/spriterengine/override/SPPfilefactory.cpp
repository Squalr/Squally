#include "SPPfilefactory.h"

#include "imagefile.h"
#include "soundfile.h"
#include "atlasfile.h"

#include "spriterfiledocumentwrapper.h"

namespace SpriterEngine
{

	FileFactory::FileFactory()
	{
	}

	FileFactory::~FileFactory()
	{
	}

	ImageFile * FileFactory::newImageFile(const std::string &initialFilePath, point initialDefaultPivot, atlasdata atlasData)
	{
		return new ImageFile(initialFilePath, initialDefaultPivot);
	}

	SoundFile * FileFactory::newSoundFile(const std::string &initialFilePath)
	{
		return new SoundFile(initialFilePath);
	}

	AtlasFile *FileFactory::newAtlasFile(const std::string &initialFilePath)
	{
		return new AtlasFile(initialFilePath);
	}

	SpriterFileDocumentWrapper * FileFactory::newScmlDocumentWrapper()
	{
		return 0;
	}

	SpriterFileDocumentWrapper * FileFactory::newSconDocumentWrapper()
	{
		return 0;
	}

}
