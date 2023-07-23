#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
};

class PlatformerEntity;
class SmartAnimationSequenceNode;
class WorldSound;

class OverworldArrow : public Projectile
{
public:
	static OverworldArrow* create(PlatformerEntity* owner, const std::string& spriteResource, float rotation = 0.0f);

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	OverworldArrow(PlatformerEntity* owner, const std::string& spriteResource, float rotation);
	virtual ~OverworldArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	float rotation = 0.0f;

	PlatformerEntity* owner = nullptr;
	cocos2d::Sprite* arrow = nullptr;
	
	WorldSound* arrowSfx = nullptr;
	WorldSound* impactSfx = nullptr;
};
