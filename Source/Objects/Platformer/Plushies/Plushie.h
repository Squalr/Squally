#pragma once
#include "cocos2d.h"

#include "Engine/Objects/Hackables/HackableObject.h"
#include "Objects/Platformer/Chest.h"

using namespace cocos2d;

class Plushie : public HackableObject
{
public:

protected:
	Plushie(ValueMap* initProperties);
	~Plushie();

	virtual void registerHackables();
	void update(float) override;

	Node* sprite;
	Chest* chest;
};
