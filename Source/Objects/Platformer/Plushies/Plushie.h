#pragma once

#include "Engine/Hackables/HackableObject.h"

class Chest;

class Plushie : public HackableObject
{
public:

protected:
	typedef HackableObject super;
	Plushie(cocos2d::ValueMap* initProperties);
	~Plushie();

	virtual void registerHackables();
	cocos2d::Vec2 getButtonOffset() override;
	void update(float) override;

	cocos2d::Node* sprite;
	Chest* chest;
};
