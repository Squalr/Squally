#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap& initProperties);

private:
	typedef HackableObject super;
	PlatformerDecorObject(cocos2d::ValueMap& initProperties);
	virtual ~PlatformerDecorObject();
};
