#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Hackables/HackableObject.h"

using namespace cocos2d;

typedef std::string CategoryName;
typedef int CategoryGroup;

class TerrainObject : public HackableObject
{
public:
	static const std::string RequestTerrainMappingEvent;

	struct TerrainMapRequestArgs
	{
		CategoryName categoryName;
		TerrainObject* collisionObject;

		TerrainMapRequestArgs(CategoryName categoryName, TerrainObject* collisionObject) : categoryName(categoryName), collisionObject(collisionObject)
		{
		}
	};

	static void requestTerrainMapping(TerrainMapRequestArgs args);

	TerrainObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CategoryName initCategoryName, bool isDynamic, bool canRotate);
	~TerrainObject();

	void setTerrainGroups(CategoryGroup categoryGroup, std::vector<CategoryGroup>* collidesWith);

	CategoryName getCategoryName();
	CategoryGroup getCategoryGroup();
	Vec2 getVelocity();
	void setVelocity(Vec2 velocity);

	virtual void setPhysicsEnabled(bool enabled);

	static std::string MapKeyTypeTerrain;

protected:
	enum TerrainDirection
	{
		None,
		Left,
		Right,
		Up,
		Down,
		StepLeft,
		StepRight,
	};

	struct TerrainData
	{
		TerrainObject* other;
		Vec2 normal;
		TerrainDirection direction;
		Vec2 points[4];
		int pointCount;

		TerrainData(TerrainObject* other, Vec2 normal, TerrainDirection direction, const Vec2* points, int pointCount)
			: other(other), normal(normal), direction(direction), pointCount(pointCount)
		{
		}
	};

	virtual bool contactBegin(TerrainData data);
	virtual bool contactUpdate(TerrainData data);
	virtual bool contactEnd(TerrainData data);

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	bool onContactBegin(PhysicsContact& contact);
	bool onContactUpdate(PhysicsContact& contact);
	bool onContactEnd(PhysicsContact& contact);

	TerrainData constructTerrainData(PhysicsContact& contact);

	CategoryName categoryName;
	PhysicsBody* physicsBody;

	bool physicsEnabled;
};
