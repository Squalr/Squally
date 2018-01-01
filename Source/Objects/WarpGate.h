#pragma once
#include "cocos2d.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class WarpGate : public CollisionObject
{
public:
	static WarpGate* create();

	void open();
	void close();

protected:
	WarpGate();
	~WarpGate();

private:

	Sprite * gateOpen;
	Sprite* gateClosed;

	bool isOpen;
};
