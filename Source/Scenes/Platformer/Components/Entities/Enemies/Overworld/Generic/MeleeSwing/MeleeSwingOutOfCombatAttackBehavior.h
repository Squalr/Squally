#pragma once

#include "Scenes/Platformer/Components/Entities/Enemies/Overworld/EnemyOutOfCombatAttackBehavior.h"

class AgroBehavior;
class Projectile;
class MainhandThrow;
class SmartAnimationSequenceNode;
class Weapon;

class MeleeSwingOutOfCombatAttackBehavior : public EnemyOutOfCombatAttackBehavior
{
public:
	static MeleeSwingOutOfCombatAttackBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MeleeSwingOutOfCombatAttackBehavior(GameObject* owner);
	virtual ~MeleeSwingOutOfCombatAttackBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;
	std::string getOutOfCombatAttackAnimation() override;
	std::string getOutOfCombatAttackSound() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;
	float getOutOfCombatAttackCooldown() override;

private:
	typedef EnemyOutOfCombatAttackBehavior super;
	
	AgroBehavior* agroBehavior = nullptr;
	PlatformerEntity* owner = nullptr;
};
