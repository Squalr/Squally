#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class PlatformerEntity;

class PlatformerAttack : public SmartNode
{
public:

	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getAttackAnimation();
	std::string getIconResource();
	void execute(PlatformerEntity* owner, PlatformerEntity* target, std::function<void(PlatformerEntity* target, int damageOrHealing)> onDamageOrHealingDelt, std::function<void()> onAttackComplete);

	virtual void onAttackTelegraphBegin();
	virtual void onDamageOrHealingDelt();
	virtual void generateProjectiles(PlatformerEntity* owner, PlatformerEntity* target, std::function<void(PlatformerEntity* target)> onTargetHit);
	virtual void onAttackEnd();
	virtual void onCleanup();

protected:
	enum AttackType
	{
		Direct,
		Projectile
	};

	PlatformerAttack(AttackType attackType, std::string iconResource, int baseDamageOrHealingMin, int baseDamageOrHealingMax, int specialCost, float attackDuration, float recoverDuration, float cleanupDuration = PlatformerAttack::DefaultCleanupDuration);
	~PlatformerAttack() = default;

	int getRandomDamageOrHealing();
	int getBaseDamageOrHealingMin();
	int getBaseDamageOrHealingMax();
	float getAttackDuration();
	float getRecoverDuration();

	static const float DefaultCleanupDuration;

private:
	typedef SmartNode super;

	AttackType attackType;
	std::string iconResource;
	int baseDamageOrHealingMin;
	int baseDamageOrHealingMax;
	int specialCost;
	float attackDuration;
	float recoverDuration;
};
