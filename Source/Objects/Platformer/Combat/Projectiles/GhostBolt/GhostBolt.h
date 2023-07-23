#pragma once

#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"

class ThrownObject;
class PlatformerAttack;
class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class GhostBolt : public ThrownObject
{
public:
	static GhostBolt* create(PlatformerEntity* owner, PlatformerEntity* target);
	
	void runSpawnFX() override;
	void runImpactFX() override;

	static const std::string HackIdentifierGhostBoltSpeed;

protected:
	GhostBolt(PlatformerEntity* owner, PlatformerEntity* target);
	virtual ~GhostBolt();

	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef ThrownObject super;

	void setGhostBoltSpeed();

	SmartAnimationSequenceNode* fireballAnim = nullptr;
	SmartAnimationSequenceNode* explosionAnim = nullptr;
	WorldSound* breathSound = nullptr;
	WorldSound* impactSound = nullptr;
};
