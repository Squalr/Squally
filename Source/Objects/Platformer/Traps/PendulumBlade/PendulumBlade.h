#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class PendulumBlade : public HackableObject
{
public:
	static PendulumBlade* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyPendulumBlade;

protected:
	PendulumBlade(cocos2d::ValueMap& initProperties);
	virtual ~PendulumBlade();

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
