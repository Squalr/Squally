#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"
#include "Objects/Interactables/Chest.h"

using namespace cocos2d;

class Plushie : public CollisionObject
{
public:

protected:
	Plushie();
	~Plushie();

	virtual void registerHackables();
	void update(float) override;

	Node* sprite;
	Chest* chest;
};
