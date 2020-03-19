#pragma once

#include "Engine/Hackables/HackableObject.h"

class IsometricDecorObject : public HackableObject
{
public:
	static IsometricDecorObject* create(cocos2d::ValueMap& properties);

protected:
	IsometricDecorObject(cocos2d::ValueMap& properties);
	virtual ~IsometricDecorObject();

private:
	typedef HackableObject super;
};
