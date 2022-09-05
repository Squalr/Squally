#pragma once

#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Waterball : public ThrownObject
{
public:
	static Waterball* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void runSpawnFX() override;
	void runImpactFX() override;

	static const std::string HackIdentifierWaterballSpeed;

protected:
	Waterball(PlatformerEntity* owner, PlatformerEntity* target);
	virtual ~Waterball();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	void setWaterballSpeed();

	SmartAnimationSequenceNode* waterballAnim = nullptr;
	SmartAnimationSequenceNode* explosionAnim = nullptr;
	WorldSound* breathSound = nullptr;
	WorldSound* impactSound = nullptr;
};
