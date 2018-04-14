#include "filereference.h"

#include "file.h"

namespace SpriterEngine
{

	FileReference::FileReference(File *initialFile) :
		file(initialFile)
	{
	}

	ImageFile *FileReference::image()
	{
		if (file)
		{
			return file->imageFile();
		}
		else
		{
			return 0;
		}
	}

	SoundFile *FileReference::sound()
	{
		if (file)
		{
			return file->soundFile();
		}
		else
		{
			return 0;
		}
	}

	void FileReference::setFile(File *newFile)
	{
		file = newFile;
	}

}
