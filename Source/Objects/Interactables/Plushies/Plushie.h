#pragma once
#include "cocos2d.h"
#include "Objects/Collision/CollisionObject.h"

using namespace cocos2d;

class Plushie : public CollisionObject
{
public:
	virtual void open();

protected:
	Plushie();
	~Plushie();

	void update(float) override;

	Sprite* sprite;

private:
	void registerHackables();

};
