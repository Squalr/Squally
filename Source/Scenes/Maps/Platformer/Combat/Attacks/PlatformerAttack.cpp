#include "PlatformerAttack.h"

using namespace cocos2d;

PlatformerAttack::PlatformerAttack(AttackType attackType, std::string iconResource, int baseDamageMin, int baseDamageMax, int specialCost, float attackDuration, float recoverDuration)
{
	this->attackType = attackType;
	this->iconResource = iconResource;
	this->baseDamageMin = baseDamageMin;
	this->baseDamageMax = baseDamageMax;
	this->specialCost = specialCost;
	this->attackDuration = attackDuration;
	this->recoverDuration = recoverDuration;
}

void PlatformerAttack::spawnProjectiles(PlatformerEntity* owner)
{
}

std::string PlatformerAttack::getAttackAnimation()
{
	return "Attack";
}

PlatformerAttack::AttackType PlatformerAttack::getAttackType()
{
	return this->attackType;
}

std::string PlatformerAttack::getIconResource()
{
	return this->iconResource;
}

int PlatformerAttack::getBaseDamageMin()
{
	return this->baseDamageMin;
}

int PlatformerAttack::getBaseDamageMax()
{
	return this->baseDamageMax;
}

float PlatformerAttack::getAttackDuration()
{
	return this->attackDuration;
}

float PlatformerAttack::getRecoverDuration()
{
	return this->recoverDuration;
}
