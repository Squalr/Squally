#pragma once

#include "Engine/Hackables/HackableObject.h"

class SoundObject : public HackableObject
{
public:
	static SoundObject* create(cocos2d::ValueMap& initProperties);

private:
	typedef HackableObject super;
	SoundObject(cocos2d::ValueMap& initProperties);
	virtual ~SoundObject();
};
