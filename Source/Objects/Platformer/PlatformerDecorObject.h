#pragma once

#include "Engine/Hackables/HackableObject.h"

class PlatformerDecorObject : public HackableObject
{
public:
	static PlatformerDecorObject* create(cocos2d::ValueMap& properties);

private:
	typedef HackableObject super;

	PlatformerDecorObject(cocos2d::ValueMap& properties);
	~PlatformerDecorObject();
};
