#pragma once
#include "cocos2d.h"

#include "Engine/Hackables/HackableObject.h"
#include "Objects/Platformer/Chest.h"

using namespace cocos2d;

class Plushie : public HackableObject
{
public:

protected:
	Plushie(ValueMap* initProperties);
	~Plushie();

	virtual void registerHackables();
	Vec2 getButtonOffset() override;
	void update(float) override;

	Node* sprite;
	Chest* chest;
};
