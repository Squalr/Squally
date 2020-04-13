#pragma once

#include "Engine/Hackables/HackableObject.h"

class SmartAnimationNode;

class Ship : public HackableObject
{
public:
	static Ship* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Ship(cocos2d::ValueMap& properties);
	virtual ~Ship();

private:
	typedef HackableObject super;

	SmartAnimationNode* ship;
};
