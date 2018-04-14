#ifndef CCSOUNDOBJECTINFOREFERENCE_H
#define CCSOUNDOBJECTINFOREFERENCE_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/override/soundobjectinforeference.h"
#include "audio/include/SimpleAudioEngine.h"

NS_CC_BEGIN

	class CC_DLL CCSoundObjectInfoReference : public SpriterEngine::SoundObjectInfoReference
	{
	public:
		CCSoundObjectInfoReference(const char* path);

		void playTrigger() override;

	private:

		const char* path;

	};

NS_CC_END

#endif // CCSOUNDOBJECTINFOREFERENCE_H
