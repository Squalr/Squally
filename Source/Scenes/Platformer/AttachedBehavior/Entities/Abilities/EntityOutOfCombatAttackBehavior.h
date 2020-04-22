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
public:
	void attack();
	
protected:
	EntityOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~EntityOutOfCombatAttackBehavior();

	void onEnter() override;
	void initializePositions() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onLoad() override;
	void onDisable() override;
	virtual Projectile* createProjectile();
	virtual void decorateProjectile(Projectile* projectile);
	virtual cocos2d::Vec2 getProjectileSpawnOffset();
	virtual float getProjectileLifetime();

	Projectile* cachedProjectile;
	WorldSound* attackSound;

protected:
	virtual std::string getOutOfCombatAttackAnimation();
	virtual std::string getOutOfCombatAttackSound();
	virtual float getOutOfCombatAttackOnset();
	virtual float getOutOfCombatAttackSustain();
	virtual float getOutOfCombatAttackCooldown();

	std::string getMainhandResource();
	std::string getOffhandResource();
	void replaceMainhandWithProjectile(Projectile* projectile);
	void replaceOffhandWithProjectile(Projectile* projectile);
	void replaceAnimationPartWithProjectile(std::string animationPart, Projectile* projectile);

private:
	typedef AttachedBehavior super;

	void tryPerformShootProjectile();

	bool isPerformingOutOfCombatAttack;

	PlatformerEntity* entity;
	cocos2d::Sprite* outOfCombatAttackDebug;
};
