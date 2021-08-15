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
	friend class BinderMechanicalFlail;

	void startSwing();
	void setSwingAngle(float angle);
	void doSwing();
	void buildChain();

	volatile float previousAngle = 0.0f;
	volatile float targetAngle = 0.0f;
	cocos2d::Sprite* joint = nullptr;
	cocos2d::Node* flailChain = nullptr;
	float flailHeight = 0.0f;
	HackableData* hackableDataTargetAngle = nullptr;
	SmartParticles* smokeParticles = nullptr;
	CollisionObject* flailCollision = nullptr;
	
	MechanicalFlailClippy* mechanicalFlailClippy = nullptr;

	static const float DefaultAngle;
	static const float SwingsPerSecondAt480Length;
	static const float MinAngle;
	static const float MaxAngle;
};
