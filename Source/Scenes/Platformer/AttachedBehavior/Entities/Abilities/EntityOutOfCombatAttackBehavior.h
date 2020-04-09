#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Projectile;
class PlatformerEntity;
class WorldSound;

class EntityOutOfCombatAttackBehavior : public AttachedBehavior
{
protected:
	EntityOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~EntityOutOfCombatAttackBehavior();

	void onEnter() override;
	void initializePositions() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void onDisable() override;
	void doOutOfCombatAttack(std::string attackAnimation, std::string soundResource, float onset, float sustain);
	virtual Projectile* createProjectile();
	virtual cocos2d::Vec2 getProjectileSpawnOffset();
	virtual float getProjectileLifetime();

	Projectile* cachedProjectile;
	WorldSound* weaponSound;

private:
	typedef AttachedBehavior super;

	void tryPerformShootProjectile();

	bool isPerformingOutOfCombatAttack;

	PlatformerEntity* entity;
	cocos2d::Sprite* outOfCombatAttackDebug;
};
