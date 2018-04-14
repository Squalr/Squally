#include "loader.h"

#include "../global/settings.h"

#include "../override/spriterfiledocumentwrapper.h"
#include "../override/filefactory.h"

namespace SpriterEngine
{
	Loader::Loader(FileFactory * newFileFactory) :
		fileFactory(newFileFactory)
	{
	}

	Loader::~Loader()
	{
	}

	void Loader::loadFile(SpriterModel * model, const std::string &fileName)
	{
		SpriterDocumentLoader spriterDocumentLoader;
		SpriterFileDocumentWrapper * wrapper = nullptr;

		SpriterFileType fileType = extractFileTypeFromFileName(fileName);
		switch (fileType)
		{
		case SPRITERFILETYPE_SCML:
			wrapper = fileFactory->newScmlDocumentWrapper();
			if (wrapper)
			{
				spriterDocumentLoader.loadFile(model, wrapper, fileName);
			}
			else
			{
				Settings::error("Loader::loadFile - attempting to load scml file \"" + fileName + "\" : no scml document wrapper found");
			}
			break;

		case SPRITERFILETYPE_SCON:
			wrapper = fileFactory->newSconDocumentWrapper();
			if (wrapper)
			{
				spriterDocumentLoader.loadFile(model, wrapper, fileName);
			}
			else
			{
				Settings::error("Loader::loadFile - attempting to load scon file \"" + fileName + "\" : no scon document wrapper found");
			}
			break;

		default:
			Settings::error("Loader::loadFile - attempting to load file \"" + fileName + "\" : unrecognized file type");
			break;
		}
		delete wrapper;
	}

	Loader::SpriterFileType Loader::extractFileTypeFromFileName(const std::string &fileName)
	{
		size_t lastDot = fileName.find_last_of(".");
		if (lastDot != std::string::npos)
		{
			std::string extension = fileName.substr(lastDot + 1, std::string::npos);

			if (extension == "scml")
			{
				return SPRITERFILETYPE_SCML;
			}
			else if (extension == "scon")
			{
				return SPRITERFILETYPE_SCON;
			}
			else
			{
				Settings::error("Loader::extractFileTypeFromFileName - file \"" + fileName + "\" : unrecognized file type");
			}
		}
		else
		{
			Settings::error("Loader::extractFileTypeFromFileName - file \"" + fileName + "\" : unable to extract extension from file name");
		}
		return SPRITERFILETYPE_NONE;
	}
}


