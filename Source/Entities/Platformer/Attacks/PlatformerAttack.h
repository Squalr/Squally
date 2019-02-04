#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class PlatformerAttack : public SmartNode
{
public:
	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getAttackAnimation();
	std::string getIconResource();

	int getBaseDamageMin();
	int getBaseDamageMax();
	float getAttackDuration();
	float getRecoverDuration();

protected:
	PlatformerAttack(std::string iconResource, int baseDamageMin, int baseDamageMax, int specialCost, float attackDuration, float recoverDuration);
	~PlatformerAttack() = default;

private:
	typedef SmartNode super;

	std::string iconResource;
	int baseDamageMin;
	int baseDamageMax;
	int specialCost;
	float attackDuration;
	float recoverDuration;
};
