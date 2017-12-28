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

protected:
	CollisionGroup getCollisionGroup();

	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

	virtual bool contactBegin(CollisionObject* other);
	virtual bool contactUpdate(CollisionObject* other);
	virtual bool contactEnd(CollisionObject* other);

private:
	void initializeEventListeners();

	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	PhysicsShape * getCollidingObject(PhysicsBody* self, PhysicsContact &contact);

	CollisionGroup collisionGroup;
	CollisionGroup collidesWith;
	PhysicsBody * physicsBody;
};
