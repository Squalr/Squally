#pragma once
#include "cocos2d.h"

#include "Objects/Collision/CategoryGroup.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableObject.h"
#include "Resources.h"

using namespace cocos2d;

class CollisionObject : public SerializableObject
{
public:
	CollisionObject(ValueMap* initProperties);
	~CollisionObject();

	void init(PhysicsBody* initPhysicsBody, CategoryGroup initCategoryGroup, bool isDynamic, bool canRotate);

	CategoryGroup getCategoryGroup();
	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

	virtual void setPhysicsEnabled(bool enabled);

	static std::string KeyTypeCollision;

protected:
	enum CollisionDirection
	{
		None,
		Left,
		Right,
		Up,
		Down,
		StepLeft,
		StepRight,
	};

	struct CollisionData
	{
		CollisionObject* other;
		Vec2 normal;
		CollisionDirection direction;
		Vec2 points[4];
		int pointCount;

		CollisionData(CollisionObject* other, Vec2 normal, CollisionDirection direction, const Vec2* points, int pointCount)
			: other(other), normal(normal), direction(direction), pointCount(pointCount)
		{
		}
	};

	virtual bool contactBegin(CollisionData data);
	virtual bool contactUpdate(CollisionData data);
	virtual bool contactEnd(CollisionData data);

	void onEnter() override;
	void update(float dt) override;

private:
	void initializeEventListeners();

	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	CollisionData constructCollisionData(PhysicsContact& contact);
	CategoryGroup getCollisionGroups();

	CategoryGroup categoryGroup;
	PhysicsBody * physicsBody;

	bool physicsEnabled;
};
