#ifndef FILE_H
#define FILE_H

#include <string>

namespace SpriterEngine
{

	class ImageFile;
	class SoundFile;
	class AtlasFile;

	class File
	{
	public:
		File(std::string initialFilePath);
		virtual ~File() {}

		virtual ImageFile *imageFile();
		virtual SoundFile *soundFile();
		virtual AtlasFile *atlasFile();

		std::string path();

	private:
		std::string filePath;
	};

}

#endif // FILE_H
