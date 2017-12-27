#pragma once
#include "cocos2d.h"
#include "Utils/Utils.h"
#include "Collision/Collision.h"

using namespace cocos2d;

static class CollisionManager : Node
{
public:
	static CollisionManager* create();

private:
	void initializeEventListeners();

	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);
};
