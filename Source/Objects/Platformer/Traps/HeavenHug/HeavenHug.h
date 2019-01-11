#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class HeavenHug : public HackableObject
{
public:
	static HeavenHug* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyHeavenHug;

protected:
	HeavenHug(cocos2d::ValueMap* initProperties);
	~HeavenHug();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void startSwing();
	void swingToAngle(float angle);
	void buildChain();
	cocos2d::PhysicsBody* createBladeCollision();

	volatile float targetAngle;
	cocos2d::Sprite* neck;
	cocos2d::Node* bladeChain;
	float chainHeight;
	HackableData* hackableDataTargetAngle;
	CollisionObject* bladeCollision;
	
	static const float DefaultAngle;
	static const float SwingsPerSecondAt480Length;
	static const float MinAngle;
	static const float MaxAngle;
};
