#pragma once

#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class ShadowBolt : public ThrownObject
{
public:
	static ShadowBolt* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void runSpawnFX() override;
	void runImpactFX();

protected:
	ShadowBolt(PlatformerEntity* owner, PlatformerEntity* target);
	virtual ~ShadowBolt();

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

	void setShadowBoltSpeed();
};
