#include "SoundObject.h"

using namespace cocos2d;

SoundObject* SoundObject::create(ValueMap& initProperties)
{
	SoundObject* instance = new SoundObject(initProperties);

	instance->autorelease();

	return instance;
}

SoundObject::SoundObject(ValueMap& initProperties) : HackableObject(initProperties)
{
}

SoundObject::~SoundObject()
{
}
