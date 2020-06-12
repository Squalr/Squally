#pragma once

#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Fireball : public ThrownObject
{
public:
	static Fireball* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void runSpawnFX() override;
	void runImpactFX() override;

	static const std::string HackIdentifierFireballSpeed;

protected:
	Fireball(PlatformerEntity* owner, PlatformerEntity* target);
	virtual ~Fireball();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	SmartAnimationSequenceNode* fireballAnim;
	SmartAnimationSequenceNode* explosionAnim;
	WorldSound* breathSound;
	WorldSound* impactSound;

	void setFireballSpeed();
};
