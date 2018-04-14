#include "CCSoundFile.h"

NS_CC_BEGIN

	CCSoundFile::CCSoundFile(std::string initialFilePath) :
		SpriterEngine::SoundFile(initialFilePath), path(initialFilePath.c_str())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(path);
	}


	SpriterEngine::SoundObjectInfoReference* CCSoundFile::newSoundInfoReference()
	{
		return new CCSoundObjectInfoReference(path);
	}

NS_CC_END