#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(ValueMap* initProperties);

private:
	PlatformerDecorObject(ValueMap* initProperties);
	~PlatformerDecorObject();
};
