#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class Projectile;
class GatlingGun;
class WorldSound;

class GatlingGunBehavior : public GameComponent
{
public:
	static GatlingGunBehavior* create(GameObject* owner);

	void attack();

	static const std::string MapKey;
	
protected:
	GatlingGunBehavior(GameObject* owner);
	virtual ~GatlingGunBehavior();

	void onEnter() override;
	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;
	virtual Projectile* createProjectile();
	virtual void decorateProjectile(Projectile* projectile);
	virtual cocos2d::Vec2 getProjectileSpawnOffset();
	virtual float getProjectileLifetime();

	Projectile* cachedProjectile = nullptr;
	WorldSound* attackSound = nullptr;

protected:
	virtual std::string getOutOfCombatAttackAnimation();
	virtual std::string getOutOfCombatAttackSound();
	virtual float getOutOfCombatAttackOnset();
	virtual float getOutOfCombatAttackSustain();
	virtual float getOutOfCombatAttackCooldown();

private:
	typedef GameComponent super;

	void tryPerformShootProjectile();

	bool isPerformingOutOfCombatAttack = false;
	GatlingGun* gatlingGun = nullptr;
};
