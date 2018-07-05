#pragma once
#include "cocos2d.h"

#include "Objects/Hackables/HackableObject.h"

using namespace cocos2d;

class IsometricDecorObject : public HackableObject
{
public:
	static IsometricDecorObject* create(ValueMap* initProperties);

private:
	IsometricDecorObject(ValueMap* initProperties);
	~IsometricDecorObject();
};
