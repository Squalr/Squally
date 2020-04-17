#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Abilities/EntityOutOfCombatAttackBehavior.h"

class AgroBehavior;
class Projectile;
class OrcBomber;
class SmartAnimationSequenceNode;
class Weapon;

class OrcBomberOutOfCombatAttackBehavior : public EntityOutOfCombatAttackBehavior
{
public:
	static OrcBomberOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcBomberOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~OrcBomberOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;
	float getOutOfCombatAttackCooldown() override;
	Projectile* createProjectile() override;

private:
	typedef EntityOutOfCombatAttackBehavior super;
	
	AgroBehavior* agroBehavior;
	Projectile* projectile;
	SmartAnimationSequenceNode* fireBreath;

	OrcBomber* orcBomber;
};
