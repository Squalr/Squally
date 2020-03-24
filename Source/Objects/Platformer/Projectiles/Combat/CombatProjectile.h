#pragma once

#include "Objects/Platformer/Projectiles/Projectile.h"

namespace cocos2d
{
	class Node;
}

class PlatformerEntity;

class CombatProjectile : public Projectile
{
public:
protected:
	CombatProjectile(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline, std::vector<cocos2d::Vec2>& hitBox, int collisionType, bool allowHacking);
	virtual ~CombatProjectile();

	void onEnter() override;

private:
	typedef Projectile super;
	
	void updateProjectileCanUpdate();

	PlatformerEntity* target;

	bool onTimeline;
	bool timelinePaused;
	bool timelinePausedCinematic;
};
