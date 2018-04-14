#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "spriterdocumentloader.h"

namespace SpriterEngine
{

	class SpriterFileDocumentWrapper;
	class SpriterModel;
	class FileFactory;

	class Loader
	{
	public:
		Loader(FileFactory *newFileFactory);
		~Loader();

		void loadFile(SpriterModel *model, const std::string &fileName);

	private:
		enum SpriterFileType
		{
			SPRITERFILETYPE_NONE,
			SPRITERFILETYPE_SCML,
			SPRITERFILETYPE_SCON
		};

		FileFactory *fileFactory;

		SpriterFileType extractFileTypeFromFileName(const std::string &fileName);
	};
}

#endif // LOADER_H
