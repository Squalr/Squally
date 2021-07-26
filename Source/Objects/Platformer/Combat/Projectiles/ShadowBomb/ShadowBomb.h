#pragma once

#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class ShadowBomb : public ThrownObject
{
public:
	static ShadowBomb* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	ShadowBomb(PlatformerEntity* owner, PlatformerEntity* target);
	virtual ~ShadowBomb();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	SmartAnimationSequenceNode* shadowBoltAnim;
	SmartAnimationSequenceNode* explosionAnim;
	WorldSound* launchSound;
	WorldSound* impactSound;

	void setShadowBombSpeed();
};
