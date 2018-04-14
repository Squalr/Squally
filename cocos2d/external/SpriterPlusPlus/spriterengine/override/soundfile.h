#ifndef SOUNDFILE_H
#define SOUNDFILE_H

#include "../file/file.h"

namespace SpriterEngine
{
	class SoundObjectInfoReference;
	class SoundFile : public File
	{
	public:
		SoundFile(std::string initialFilePath);

		SoundFile *soundFile();

		// override to create a custom sound object that can playback sound with void playTrigger();
		virtual SoundObjectInfoReference *newSoundInfoReference();
	};

}

#endif // SOUNDFILE_H
