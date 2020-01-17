#pragma once

#include "Objects/Platformer/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class Fireball : public ThrownObject
{
public:
	static Fireball* create(PlatformerEntity* owner);
	
	void runSpawnFX() override;
	void runImpactFX();

protected:
	Fireball(PlatformerEntity* owner);
	virtual ~Fireball();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	SmartAnimationSequenceNode* explosionAnim;
	WorldSound* breathSound;
	WorldSound* impactSound;

	void setFireballSpeed();
};
