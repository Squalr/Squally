#pragma once

#include "Engine/Hackables/HackableObject.h"

class IsometricDecorObject : public HackableObject
{
public:
	static IsometricDecorObject* create(cocos2d::ValueMap* initProperties);

private:
	IsometricDecorObject(cocos2d::ValueMap* initProperties);
	~IsometricDecorObject();
};
