#pragma once
#include <set>

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class HackableData;
class LiquidNode;

class Water : public GameObject
{
public:
	static Water* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyWater;

protected:
	Water(cocos2d::ValueMap& initProperties);
	virtual ~Water();
	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;
	void applyWaterForce(const std::vector<CollisionObject*>& targets, float dt);

private:
	typedef GameObject super;

	CollisionObject* waterCollision;
	LiquidNode* water;

	cocos2d::Size waterSize;
	float elapsed;

	static const float WaterGravity;
};
