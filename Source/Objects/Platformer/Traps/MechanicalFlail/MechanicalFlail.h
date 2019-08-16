#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ParticleSystemQuad;
	class Sprite;
}

class CollisionObject;
class HackableData;

class MechanicalFlail : public HackableObject
{
public:
	static MechanicalFlail* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyMechanicalFlail;

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
	void swingToAngle(float angle);
	void buildChain();

	volatile float targetAngle;
	cocos2d::Sprite* joint;
	cocos2d::Node* flailChain;
	float flailHeight;
	HackableData* hackableDataTargetAngle;
	cocos2d::ParticleSystemQuad* smokeParticles;
	CollisionObject* flailCollision;

	static const float DefaultAngle;
	static const float SwingsPerSecondAt480Length;
	static const float MinAngle;
	static const float MaxAngle;
};
