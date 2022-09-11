#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

class SmartAnimationSequenceNode;
class WorldSound;

class OverworldShadowBolt : public Projectile
{
public:
	static OverworldShadowBolt* create();

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	OverworldShadowBolt();
	virtual ~OverworldShadowBolt();

	void onEnter() override;

private:
	typedef Projectile super;

	WorldSound* shadowBoltSfx = nullptr;
	WorldSound* impactSfx = nullptr;

	SmartAnimationSequenceNode* shadowBolt = nullptr;
	SmartAnimationSequenceNode* explosion = nullptr;
};
