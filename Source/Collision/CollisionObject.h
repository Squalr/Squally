#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/CollisionGroup.h"

using namespace cocos2d;

class CollisionObject : public Node
{
public:
	CollisionObject();
	~CollisionObject();

	void init(PhysicsBody* initPhysicsBody, CollisionGroup initCollisionGroup, CollisionGroup initCollidesWith);
	void init(PhysicsBody* initPhysicsBody, CollisionGroup initCollisionGroup);

	CollisionGroup getCollisionGroup();
	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

protected:
	struct CollisionData
	{
		CollisionObject* other;
		bool isCollisionBelow;

		CollisionData(CollisionObject* other, bool isCollisionBelow) : other(other), isCollisionBelow(isCollisionBelow)
		{
		}
	};

	virtual bool contactBegin(CollisionData data);
	virtual bool contactUpdate(CollisionData data);
	virtual bool contactEnd(CollisionData data);

private:
	void initializeEventListeners();

	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	CollisionData constructCollisionData(PhysicsContact& contact);
	bool isContactBelow(Node* node, PhysicsContact &contact);

	CollisionGroup collisionGroup;
	CollisionGroup collidesWith;
	PhysicsBody * physicsBody;
};
