#pragma once

#include "Engine/Hackables/HackableObject.h"

class IsometricDecorObject : public HackableObject
{
public:
	static IsometricDecorObject* create(cocos2d::ValueMap& properties);

private:
	typedef HackableObject super;
	IsometricDecorObject(cocos2d::ValueMap& properties);
	~IsometricDecorObject();
};
