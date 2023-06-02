#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;
class WorldSound;

class OverworldArrow : public Projectile
{
public:
	static OverworldArrow* create(PlatformerEntity* owner, const std::string& spriteResource);

	void runSpawnFX() override;
	void runImpactFX() override;

protected:
	OverworldArrow(PlatformerEntity* owner, const std::string& spriteResource);
	virtual ~OverworldArrow();

	void onEnter() override;

private:
	typedef Projectile super;

	PlatformerEntity* owner = nullptr;
	cocos2d::Sprite* arrow = nullptr;
	
	WorldSound* arrowSfx = nullptr;
	WorldSound* impactSfx = nullptr;
};
