#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/Hackables/HackableObject.h"

typedef std::string CategoryName;
typedef int CategoryGroup;

namespace cocos2d
{
	class PhysicsBody;
	class PhysicsContact;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject : public HackableObject
{
public:
	static const std::string RequestCollisionMappingEvent;

	struct CollisionMapRequestArgs
	{
		CategoryName categoryName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(CategoryName categoryName, CollisionObject* collisionObject) :
				categoryName(categoryName), collisionObject(collisionObject)
		{
		}
	};

	static void requestCollisionMapping(CollisionMapRequestArgs args);

	CollisionObject(cocos2d::ValueMap* initProperties, cocos2d::PhysicsBody* initPhysicsBody,
			CategoryName initCategoryName, bool isDynamic, bool canRotate);
	virtual ~CollisionObject();

	void setCollisionGroups(CategoryGroup categoryGroup, std::vector<CategoryGroup>* collidesWith);

	CategoryName getCategoryName();
	CategoryGroup getCategoryGroup();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);

	virtual void setPhysicsEnabled(bool enabled);

	static std::string MapKeyTypeCollision;

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
		cocos2d::Vec2 normal;
		CollisionDirection direction;
		cocos2d::Vec2 points[4];
		int pointCount;

		CollisionData(CollisionObject* other, cocos2d::Vec2 normal, CollisionDirection direction,
				const cocos2d::Vec2* points, int pointCount) :
			other(other), normal(normal), direction(direction), pointCount(pointCount)
		{
		}
	};

	virtual bool contactBegin(CollisionData data);
	virtual bool contactUpdate(CollisionData data);
	virtual bool contactEnd(CollisionData data);

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);

	CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);

	CategoryName categoryName;
	cocos2d::PhysicsBody* physicsBody;

	bool physicsEnabled;
};
