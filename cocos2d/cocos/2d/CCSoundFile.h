#ifndef CCSOUNDFILE_H
#define CCSOUNDFILE_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/override/soundfile.h"
#include "SpriterPlusPlus/spriterengine/global/settings.h"
#include "CCSoundObjectInfoReference.h"
#include "audio/include/SimpleAudioEngine.h"

NS_CC_BEGIN

	class CC_DLL CCSoundFile : public SpriterEngine::SoundFile
	{
	public:
		CCSoundFile(std::string initialFilePath);

		SpriterEngine::SoundObjectInfoReference* newSoundInfoReference() override;

	private:
		const char* path;
	};

NS_CC_END

#endif // CCSOUNDFILE_H
