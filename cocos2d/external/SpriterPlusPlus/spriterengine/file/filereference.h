#ifndef FILEREFERENCE_H
#define FILEREFERENCE_H

namespace SpriterEngine
{

	class File;
	class ImageFile;
	class SoundFile;

	class FileReference
	{
	public:
		FileReference(File *initialFile);

		ImageFile *image();
		SoundFile *sound();

		void setFile(File *newFile);

	private:
		File *file;
	};

}

#endif // FILEREFERENCE_H
