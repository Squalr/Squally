#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/GlobalNode.h"
#include "Engine/Physics/CollisionObject.h"

typedef int CollisionType;

class CollisionEventDispatcher : public GlobalNode
{
public:
	static void registerGlobalNode();

protected:
	void initializeListeners() override;

private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);

	static CollisionEventDispatcher* instance;
};
