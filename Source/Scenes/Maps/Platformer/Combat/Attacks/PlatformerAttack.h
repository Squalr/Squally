#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;
class PlatformerEntity;

class PlatformerAttack : public SmartNode
{
public:
	enum AttackType
	{
		Direct,
		Projectile
	};

	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getAttackAnimation();
	AttackType getAttackType();
	std::string getIconResource();
	int getBaseDamageMin();
	int getBaseDamageMax();
	float getAttackDuration();
	float getRecoverDuration();

	virtual void spawnProjectiles(PlatformerEntity* owner);

protected:
	PlatformerAttack(AttackType attackType, std::string iconResource, int baseDamageMin, int baseDamageMax, int specialCost, float attackDuration, float recoverDuration);
	~PlatformerAttack() = default;

private:
	typedef SmartNode super;

	AttackType attackType;
	std::string iconResource;
	int baseDamageMin;
	int baseDamageMax;
	int specialCost;
	float attackDuration;
	float recoverDuration;
};
