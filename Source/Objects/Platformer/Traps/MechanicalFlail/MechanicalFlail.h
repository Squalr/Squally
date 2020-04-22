#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class MechanicalFlailClippy;
class SmartParticles;

class MechanicalFlail : public HackableObject
{
public:
	static MechanicalFlail* create(cocos2d::ValueMap& properties);

	static const std::string HackIdentifierTargetAngle;
	static const std::string MapKey;

protected:
	MechanicalFlail(cocos2d::ValueMap& properties);
	virtual ~MechanicalFlail();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void startSwing();
	void setSwingAngle(float angle);
	void doSwing();
	void buildChain();

	volatile float previousAngle;
	volatile float targetAngle;
	cocos2d::Sprite* joint;
	cocos2d::Node* flailChain;
	float flailHeight;
	HackableData* hackableDataTargetAngle;
	SmartParticles* smokeParticles;
	CollisionObject* flailCollision;
	
	MechanicalFlailClippy* mechanicalFlailClippy;

	static const float DefaultAngle;
	static const float SwingsPerSecondAt480Length;
	static const float MinAngle;
	static const float MaxAngle;
};
