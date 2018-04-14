#include "CCSoundObjectInfoReference.h"

NS_CC_BEGIN

	CCSoundObjectInfoReference::CCSoundObjectInfoReference(const char* path)
	: path(path) {}

	void CCSoundObjectInfoReference::playTrigger()
	{
		if (getTriggerCount())
		{
            auto engine = CocosDenshion::SimpleAudioEngine::getInstance();
            engine->playEffect(path,false,1.0f,float(getPanning()),float(getVolume()));
		}
	}

NS_CC_END