#pragma once

#include "Engine/Hackables/HackableObject.h"

class HackableData;

namespace cocos2d
{
	class ParticleSystemQuad;
	class Sprite;
}

class CollisionObject;

class MechanicalFlail : public HackableObject
{
public:
	static MechanicalFlail* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMechanicalFlail;

protected:
	MechanicalFlail(cocos2d::ValueMap* initProperties);
	~MechanicalFlail();

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
