#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class PendulumBladeClippy;

class PendulumBlade : public HackableObject
{
public:
	static PendulumBlade* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyPendulumBlade;

protected:
	PendulumBlade(cocos2d::ValueMap& properties);
	virtual ~PendulumBlade();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void startSwing();
	void swingToAngle(float angle);
	void buildChain();
	std::vector<cocos2d::Vec2> createBladeCollision();

	volatile float targetAngle;
	cocos2d::Sprite* neck;
	cocos2d::Node* bladeChain;
	float chainHeight;
	HackableData* hackableDataTargetAngle;
	CollisionObject* bladeCollision;

	PendulumBladeClippy* pendulumBladeClippy;
	
	static const float DefaultAngle;
	static const float SwingsPerSecondAt480Length;
	static const float MinAngle;
	static const float MaxAngle;
};
