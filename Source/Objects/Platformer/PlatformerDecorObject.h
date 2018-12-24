#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap* initProperties);

private:
	PlatformerDecorObject(cocos2d::ValueMap* initProperties);
	~PlatformerDecorObject();
};
