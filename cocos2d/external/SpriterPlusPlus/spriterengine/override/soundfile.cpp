#include "soundfile.h"

#include "soundobjectinforeference.h"

namespace SpriterEngine
{
	SoundFile::SoundFile(std::string initialFilePath) :
		File(initialFilePath)
	{
	}

	SoundFile *SoundFile::soundFile()
	{
		return this;
	}

	SoundObjectInfoReference * SoundFile::newSoundInfoReference()
	{
		return new SoundObjectInfoReference();
	}

}
